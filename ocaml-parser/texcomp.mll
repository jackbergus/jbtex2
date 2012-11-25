(**
 * texcomp.mll
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
{ open Debug
  open Texrule
  let incr x = c:=!c+x;;
 }

(**Giacomo Bergami: Lexer File *)

(* regole generali *)
rule token = parse
   '$'  		{ incr 1; MathSimpl 	}
  | ".%"		{ incr 2; Cend		}
  | "\\\\"              { incr 2; Area("\\\\")  }
  | "\n"                { k:=!k+1; c:=0; Area("\n")    }
  | "%-"		{ comment lexbuf }		
  | '%'(['A'-'z' '0'-'9']+)  { Cbegin(Lexing.lexeme lexbuf) 	   }
  | "%include "          { filein lexbuf }
  | "\\["     		{ MathOpen  	}
  | "\\]"     		{ MathClose 	}
  | "\\rm "		{ Rm(" ")    	}
  | "\\rm{"		{ Rm("{")    	}
  | "\\bf "     	{ Bf(" ")		}
  | "\\bf{"    		{ Bf("{")		}
  | "\\tt "		{ Tt(" ")		}
  | "\\sf " 		{ Sf(" ")		}
  | "\\it " 		{ It(" ")		}
  | "\\tt{"		{ Tt("{")		}
  | "\\sf{" 		{ Sf("{")		}
  | "\\it{" 		{ It("{")		}
  | "\\math{"		{ MNormal("{")	}
  | "\\math "		{ MNormal(" ")	}
  | "\\cal{"            { Cal("{") }
  | "\\cal "            { Cal(" ") }
  | ":="		{ issetto lexbuf }
  | "\\:="              { Area(":=") }
  | eof			{ Eof 	}
  | _        		{ Area(Lexing.lexeme lexbuf) 	}

  


(* area commenti *)
and comment = parse
    "-%"		{ token lexbuf  	}
  | _                   { comment lexbuf 	}

(* area definizioni *)
and issetto = parse 
    [^ '\n']*  	     	{ Arg(Lexing.lexeme lexbuf) }
  | _                	{ token lexbuf     }


and filein = parse
    ":="             	{ Setfile }
  | ['0'-'9']+ as t  	{ Pos(int_of_string t)  }
  | "/"              	{ NBreak }
  | ".%"  	     	{ token lexbuf }
  | _              	{ Area(Lexing.lexeme lexbuf) }
  
    

