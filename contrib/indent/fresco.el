;;; Basic Fresco coding style for Emacs
;;; To use:
;;;   1) load this file, or copy it into your .emacs, or whatever.
;;;   2) then do one of:
;;;     2a) Set the variable c-default-style to "fresco" (using M-x customize
;;;         or setq or whatever)
;;;     2b) Use C-c . fresco to set the style manually per-buffer
;;;     2c) Put the following line into a C++ file:
;;;       // -*- mode: c++; c-file-style: fresco -*-

;;; Known bugs:
;;;   -- uses 4 spaces of indentation for namespaces, instead of 2
;;;   -- class access labels are indented 0 spaces, instead of 2
;;; probably lots more of improvements possible, but this is a start
;;; If you find any particular problems or fixes, post to issues.fresco.org.

(c-add-style "fresco" 
             '((c-basic-offset . 4) 
               (c-offsets-alist (innamespace       . *) 
                                (access-label      . /) 
                                (inline-open       . +) 
                                (inline-close      . 0) 
                                (substatement-open . 0)) 
 
               (c-hanging-braces-alist (class-close before) 
                                       (inline-open nil) 
                                       (inline-close after)) 
 
               (c-hanging-colons-alist (access-label after) 
                                       (member-init-intro after)) 
               (c-hanging-semi&comma-criteria
                c-semi&comma-no-newlines-for-oneline-inliners 
                c-semi&comma-inside-parenlist)))