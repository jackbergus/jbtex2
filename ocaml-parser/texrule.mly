%{
(**
 * texrule.mly
 * This file is part of jbtex2
 *
 * Copyright (C) 2012 - Giacomo Bergami <giacomo90@libero.it>
 *
 * jbtex2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * jbtex2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jbtex2; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *)
(** Giacomo Bergami: Parsing File *)
let reform s = String.sub s 1 ((String.length s)-1)

let readlines f =
  let lines = ref [] in
  let chan = open_in f in
   try
     while true; do
       lines := input_line chan :: !lines
     done; []
   with End_of_file ->
      ( close_in chan;
        List.rev !lines)

let rec fromto ls a b =
    match ls with
     | [] -> if (b==0) then [] else (failwith "Out of ls")
     | h::tl -> if (a>0) then (fromto tl (a-1) (b-1)) else
                  if (b>0) then h::(fromto tl a (b-1)) else [h]
                  
let appendimport f a b =
   let st = (List.fold_right (^) (fromto (readlines f) a b) "") in
     String.sub st 0 ((String.length st)-1)

%}

%token <string> Area
%token MathSimpl MathOpen MathClose Rm Eof Include Setfile NBreak
%token Cend
%token <string> Cbegin Arg Bf Tt Sf It 
%token <string> Rm
%token <string> MNormal
%token <int>    Pos
%token <string> Cal

%start main
%type <string> main
%%

 /* tipi matematici */
 math: 
	  MathSimpl cmath MathSimpl 	{ "$"^$2^"$"		}
      	| MathOpen  cmath MathClose	{ "\\["^$2^"\\]" 	};

 /* inizio */
 main:  maina Eof 			{ $1	};

 /* ricorsione sul main */
 maina:
 	  maina tipo			{ $1^$2	}
 	| tipo				{ $1	};


 /* ARGOMENTI DEL BEGIN */
 al:	
 	  Arg al			{ $1^$2 }
 	| Arg				{ $1 };

 /* DATI IN COMUNE A MATEMATICI E MENO */
 symbol:
 	  Rm				{ "rm"^$1 }
 	| Bf				{ "bf"^$1 }
 	| Tt				{ "tt"^$1 }
 	| Sf				{ "sf"^$1 }
 	| It				{ "it"^$1 }
 	| Cal                           { "cal"^$1 };

 /* DATI NON MATEMATICI */
 nmath: 
	| symbol maina 					{ "\\text"^$1^$2 }
 	| Area 						{ $1 		     };


 /* DATI IN CAMPI MATEMATICI */
 lmath: 
          symbol 			{ "\\math"^$1^"" }
	| MNormal 	       		{ "\\mathnormal" }
	| Area                          { $1 };
	| Cbegin cmath Cend		{ "\\begin{"^(reform $1)^"}"^$2^"\\end{"^(reform $1)^"}" }
 	| Cbegin al cmath Cend		{ "\\begin{"^(reform $1)^"}["^$2^"]"^$3^"\\end{"^(reform $1)^"}" }

/*nota: ho invertito l'ordine di inclusione dei cmath */
 cmath:
 	  lmath				{ $1	}
	| lmath	cmath			{ $1^$2 };

 tipo:  
 	  nmath				{ $1 }
 	| math				{ $1 }
 	| Cbegin maina Cend		{ "\\begin{"^(reform $1)^"}"^$2^"\\end{"^(reform $1)^"}" }
 	| Cbegin al maina Cend		{ "\\begin{"^(reform $1)^"}["^$2^"]"^$3^"\\end{"^(reform $1)^"}" }
 	| maina Setfile Pos NBreak Pos  {  appendimport $1 $3 $5 };
