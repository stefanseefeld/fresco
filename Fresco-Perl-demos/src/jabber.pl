#!/usr/bin/perl-thread

my $version = "0.0";

use Net::Jabber;

#$^W = 1;
$| = 1;
use Warsaw;

use Command_impl;

use strict;
my ($user, $pass) = @ARGV;

$pass || die "Usage: $0 user\@host/resource password";

my $con = undef;
my $kits = Warsaw::Utility::war_connect(`get-nameservice-ior`);
my $convs = {};

# Main
$user =~ m|(.*)@(.*)(/(.*))?|;
my $uid = $1;
my $host = $2;
my $resource = $4 || "default";
my $buf;

#start_gui();
#my $c = new_conversation("bob");
#my $line = $kits->{TextKit}->chunk(Warsaw::Utility::asc2uni("FOO!"));
#$c->{body}->append($line);
my $buf = $kits->{CommandKit}->text();
$buf->insertString(Warsaw::Utility::asc2uni("this is string"));
print "Length of buffer is ", $buf->size(), "\n";
my $result = $buf->value();
print "and contains \"", Warsaw::Utility::uni2asc($result), "\"\n";
jab_connect($uid, $host, $resource, $pass);
main_loop();

#print "Got window, trying to add some text...\n";
#$buf->insertString(Warsaw::Utility::asc2uni("Hello world!"));
#print "did it show up?\n";

sub start_gui() {
    $buf = $kits->{CommandKit}->text();
    $buf->insertString(Warsaw::Utility::asc2uni("Hello world!"));
    my $txt = $kits->{TextKit}->simpleViewer($buf);
#    my $spec = ToolKit::FrameSpec->new(ToolKit::outset);
#    $spec->bbrightness(0.5);
    my $rgb = $kits->{ToolKit}->rgb($txt, 1, 1, 1);
#    my $frame = $kits->{ToolKit}->frame($rgb,
#					10,
#					$spec,
#					1);

    my $input = $kits->{ToolKit}->textInput($rgb, $buf);
    my $margin = $kits->{LayoutKit}->margin($input, 200);
    my $outset = $kits->{ToolKit}->outset($margin,
					  Color->new(red => .6,
						     blue => .6,
						     green => .6,
						     alpha => 1),
					  1);
#    my $group = $kits->{ToolKit}->group($margin);
#    my $window = $kits->{DesktopKit}->shell($group);
    my $group = $kits->{ToolKit}->group($txt);
    my $window = $kits->{DesktopKit}->shell($group);
}

sub new_conversation($) {
    my ($name) = @_;
    
    my $vbox = $kits->{LayoutKit}->vbox();

# Text display at top
    my $text = $kits->{LayoutKit}->vbox();
    my $decorated_text = $kits->{ToolKit}->rgb($text, 1, 1, 1);
    my $area = $kits->{LayoutKit}->fixedSize($decorated_text,
					     5000,
					     5000,);
#    my $pager = $kits->{WidgetKit}->scrollable($decorated_text);
#    my $decorated_pager = $kits->{ToolKit}->rgb($pager, 0, 0, 0);
#    my $area = $kits->{LayoutKit}->fixedSize($decorated_pager,
#					     2000,
#					     2000,);
    my $pager = $kits->{WidgetKit}->scrollable($kits->{ToolKit}->rgb($area,
								     0,
								     0,
								     0,));
    my $fixed_pager = $kits->{LayoutKit}->fixedSize($pager,
						    2000,
						    2000,);
    $vbox->append($fixed_pager);


# entry window
    my $buf = $kits->{CommandKit}->text();
    $buf->insertString(Warsaw::Utility::asc2uni("enter message here"));
    my $entry = $kits->{TextKit}->simpleViewer($buf);
    my $decorated_entry = $kits->{ToolKit}->rgb($entry, 1, 1, 1);
#      my $spec = ToolKit::FrameSpec->new(ToolKit::outset);
#      $spec->bbrightness(0.5);
#      my $entry_frame = $kits->{ToolKit}->frame($decorated_entry,
#    					      10,
#    					      $spec,
#    					      1);
    my $entry_margin = $kits->{LayoutKit}->margin($decorated_entry, 25);
#    my $decorated_entry_margin = $kits->{ToolKit}->rgb($entry_margin, 0, 0, 0);
    my $editable = $kits->{ToolKit}->textInput($entry_margin, $buf);
#    $vbox->append($editable);
    $vbox->append($editable);
#    $vbox->append($entry_frame);


# buttons along bottom
    my $buttons = $kits->{LayoutKit}->hbox();

    # "Send" button
    my $send_label = $kits->{TextKit}->chunk(Warsaw::Utility::asc2uni("Send"));
    $send_label = $kits->{LayoutKit}->margin($send_label, 20);
    $send_label = $kits->{ToolKit}->rgb($send_label, 0, 0, 0);
    # FIXME: does sticking undef here work?
    my $send = $kits->{WidgetKit}->button($send_label,
					  SendCommand->new(name => $name));

    # "Close" button
    my $close_label = $kits->{TextKit}->chunk(Warsaw::Utility::asc2uni("Close"));
    $close_label = $kits->{LayoutKit}->margin($close_label, 20);
    $close_label = $kits->{ToolKit}->rgb($close_label, 0, 0, 0);
    my $close = $kits->{WidgetKit}->button($close_label, undef);

    my $hfil = $kits->{LayoutKit}->hfil();
    $buttons->append($hfil);
    $buttons->append($send);
    $buttons->append($hfil);
    $buttons->append($close);
    $buttons->append($hfil);
    $vbox->append($buttons);

    my $margin = $kits->{LayoutKit}->margin($vbox, 200);
    my $group = $kits->{ToolKit}->group($margin);
    $group->appendController($pager);
    $group->appendController($editable);
    $group->appendController($send);
    $group->appendController($close);
    my $window = $kits->{DesktopKit}->shell($group);

    $close->action($window->map(0));

    return { window => $window, body => $text, entry => $buf };
}

sub jab_connect($$$$) {
    my ($uid, $host, $resource, $pass) = @_;
    
    if (!defined($pass)) {
	return "Error: bad call to connect()";
    }

    $con = Net::Jabber::Client->new();
    $con->Connect( name => $host );
    $con->SetCallBacks(message => \&message_handler,
		       presence => \&presence_handler,
		       iq => \&iq_handler, );
    my @err = $con->AuthSend(username => $uid, password => $pass, resource => $resource);
    (@err[0] eq "ok") or return @err[1];
    
    my $pres = Net::Jabber::Presence->new();
    $con->Send($pres);

    return 0;
}

sub main_loop() {
    print "Entering main loop\n";
    while (1) {
	$con->Process();
	print "Looping\n";
    }
}

sub message_handler {
    my $m = new Net::Jabber::Message(@_);

    if ($m->GetType() eq "error") {
	print "got an error message ", @_, "\n";
	return;
    }
    
    print("Received message from ", $m->GetFrom(), " saying ",
	  $m->GetBody(), "\n");
    my $name = $m->GetFrom();
    $name =~ m/^(.*)\@/;
    my $uid = $1;
    print "(uid is $uid)\n";
    my $body = $m->GetBody();
    if (!defined($convs->{$name})) {
	$convs->{$name} = new_conversation($name);
    }
    print("window is ",
	  ($convs->{$name}->{window}->mapped() ? "mapped" : "unmapped"),
	  "\n");
    if (! $convs->{$name}->{window}->mapped()) {
# blank out $convs->{$name}->{text} ?
	use COPE::CORBA::Any;
	$convs->{$name}->{window}->map(1)->execute(CORBA::Any->new());
    }

    my $line = $kits->{TextKit}->chunk(Warsaw::Utility::asc2uni("$uid:$body"));
    $convs->{$name}->{body}->append($line);
    $line->needRedraw();
}

use Data::Dumper;
sub presence_handler {
    print "Received presence:\n";
    print Dumper(@_);
}

sub iq_handler {
    print "Received iq:\n";
    print Dumper(@_);
}

package SendCommand;
use vars qw(@ISA);
BEGIN {
    @ISA = qw(Command_impl);
}

# create as SendCommand->new(name => "name")
# FIXME: why aren't we getting CORBA::BOA::_Servant::new?

sub execute($$) {
    my ($self, $any) = @_;

    print "Called SendCommand->execute()\n";
    
    my $name = $self->{name};
    my $body = $convs->{$name}->{body};
    my $entry = $convs->{$name}->{entry};

#    my $text = Warsaw::Utility::uni2asc($entry->getChars(0, $entry->size()));
    my $text = Warsaw::Utility::uni2asc($entry->value());
    print "User entered $text for $name\n";
    my $line = $kits->{TextKit}->chunk(Warsaw::Utility::asc2uni("$uid: $text"));
    $body->append($line);
    $line->needRedraw();

    $con->MessageSend(to => $name, body => $text);
}
