(**
 * loader.ml
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
(* you could use this simple loader in order to execute the compiler.ml function
   by typing 

   #use "loader.ml" 
*)
#load "texcomp.cmo";;
#load "openvars.cmo";;
#load "texrule.cmo";;
#use "compiler.ml";;
