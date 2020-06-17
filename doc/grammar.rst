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
                 letter , { letter | '_' }
                 ;

               number =
                 [ '-' ], digit, { digit }
                 ;
                  
-----------

Sort
****

.. code-block:: ebnf

                sort =
                  identifier, '(', 'A', ')', '{',
                    [ declaration ]
                  '}'
                  ;
                  
.. code-block:: text

                SortNameFoo(A) {
                  declaration { ... }
                }

-----------
                
Declaration
***********

.. code-block:: ebnf

                declaration =
                  'declaration', '{', { identifier, ':', type ',' } '}'
                  ;
                
                type =
                  'integer'
                  ;
                   
.. code-block:: text

           declaration {
             i:integer,
             j:integer,
           }

-----------
           
Implemenation
*************

TODO

-----------
                 
Example
*******

.. code-block:: text

                bubbleSort(A)
                {
                  declaration {
                    i integer,
                    j integer,
                  }
                  
                  implementation {
                    for i <- sizeof(A) - 1 to 1 by -1 {
                      for j <- 0 to i - 1 by 1 {    
                        if T[j + 1] < T[j] { 
                          swap T[j], T[j + 1]
                        }
                      }
                    }
                  }
                }
