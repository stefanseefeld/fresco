" Fresco VIM Script
" Implements coding guidelines at http://www2.fresco.org/coding-style.html

" general
set tw=78               " textwidth of 78 chars, will break at whitespace

" tabs
set sw=4                " 4 spaces for shiftwidth
set ts=4                " 2 spaces for tabs
set sts=2               " 2 spaces for softtabstop
set expandtab           " changes tabs to spaces

" cindent options
set formatoptions=tcqro	" this will allow needed C-comment style
set cinoptions=g0.5s,h0.5s,t0
set cindent             " indent on cinwords
