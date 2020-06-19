*******
Grammar
*******

**The goal of this document is to describe the grammar of the sort algorithm language.**

We are using `EBNF <https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form>`_ as a grammar notation.

.. contents:: Table of contents
              :local:
               
-----------
                 
Basics
******

.. code-block:: ebnf

                letter =
                  'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' |
                  'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' |
                  'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' |
                  'V' | 'W' | 'X' | 'Y' | 'Z' | 'a' | 'b' |
                  'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' |
                  'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' |
                  'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' |
                  'x' | 'y' | 'z'
                  ;

               digit =
                 '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
                 ;

               identifier =
                 letter { letter | '_' }
                 ;

               number =
                 [ '-' ] digit { digit }
                 ;

-----------

Type
****

.. code-block:: ebnf

                type =
                  'integer' |
                  'array'
                  ;

-----------

Variable declaration
********************

.. code-block:: ebnf

                list_vardec =
                  vardec { ',' vardec }
                  ;
                
                vardec =
                  empty |
                  identifer ':' type
                  ;

.. code-block:: text

                i:integer,
                j:integer
                  
-----------

Sort
****

.. code-block:: ebnf

                sort =
                  identifier '(' list_vardec ')' '{' [ declaration ] '}'
                  ;
                  
.. code-block:: text

                SortNameFoo(...) {
                  ...
                }

-----------
                
Declaration
***********

.. code-block:: ebnf

                declaration =
                  'declaration' '{' list_vardec '}'
                  ;
                                   
.. code-block:: text

                declaration {
                  ...
                }

-----------
           
Implemenation
*************

TODO

                 
