# utility module to do basic in Berlin stuff
package Warsaw::Utility;

use COPE::CORBA::ORB;
use Experimental::Exception;
use COPE::CORBA::Exception;

use Unicode::String qw(ucs2 utf8);
use Unicode::Map8;
use Thread qw(async);

use lib 'Warsaw';
use Warsaw::Warsaw;
# should we use Warsaw::Warsaw_skel; here?

use lib 'impl';
use ClientContext_impl;


require Exporter;
use vars qw(@ISA @EXPORT @EXPORT_OK @EXPORT_TAGS);

@ISA = qw(Exporter);
@EXPORT = ();
@EXPORT_OK = qw(war_connect asc2uni uni2asc);
%EXPORT_TAGS = (all => [ @EXPORT_OK ],
		text => [ qw(asc2uni uni2asc) ]);

BEGIN {
    use Carp;
    $SIG{__DIE__} = sub { confess(@_); };
}


# takes a nameserver ior, returns a reference to a hash of kits
sub war_connect($) {
    my ($ior) = @_;

    my $orb = CORBA::ORB_init();
    my $boa = $orb->BOA_init();

    my $boa_thr = async {
	$boa->impl_is_ready(1);
    };
    $boa_thr->detach();
    
    my $context = CosNaming::NamingContext->_narrow($orb->string_to_object($ior));

    my $obj = $context->resolve([ { id => Server->_interface(), kind => "Object" } ]);
    my $manager = Server->_narrow($obj);
    my $client = ClientContext_impl->new();
    my $server = $manager->newServerContext($client);

    my $kits = { TextKit => '',
		 DesktopKit => '',
		 LayoutKit => '',
		 ToolKit => '',
		 WidgetKit => '',
		 FigureKit => '',
		 CommandKit => '',
		 ImageKit => '', };
    foreach my $kit (keys %$kits) {
	my $inter = "IDL:" . $kit . ":1.0";  # silly hack, for now
	$kits->{$kit} = $server->resolve($inter, []);
	eval $kit . '->_narrow($kits->{' . $kit . '})';
	print "Got $kit\n";
    }

    return $kits;
}

my $unimap = Unicode::Map8->new("US-ASCII");
# turns a string into an integer listref
sub asc2uni($) {
    my $ascii = shift;
    return [ (ucs2($unimap->to16($ascii)))->unpack() ];
}
# turns an integer listref into a string (of ascii; should fix this eventually
# using perl's utf8 support)
# FIXME: does this routine even work?
sub uni2asc($) {
    my $unicode = Unicode::String->new();
    $unicode->pack(@{shift()});
    return $unicode->latin1();
}
    
1;
