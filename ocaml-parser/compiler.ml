(**
 * compiler.ml
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

    (* This file contains the main part of the compiler*)

open Debug
open Texcomp
open Texrule
open Printf


let load_file f_name = 
 try
  let lb = Lexing.from_channel (open_in f_name) in
    Texrule.main Texcomp.token lb
 with _ -> failwith ("Error at line "^(string_of_int !k))


let write fil st=
let oc = open_out fil in 
  begin
  fprintf oc "%s" st; 
  close_out oc; 
  end

let compile fin fout =
  write fout (load_file fin);;

(*Callback.register "jbcompile" compile;;*)

let _ = printf "jb2tex  Copyright (C) 2011  Giacomo Bergami\n";
	printf "compiling %s...\n" Sys.argv.(1);
        write (Sys.argv.(1)^".tex") (load_file Sys.argv.(1));;
