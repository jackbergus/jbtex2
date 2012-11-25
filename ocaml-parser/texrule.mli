type token =
  | Area of (string)
  | MathSimpl
  | MathOpen
  | MathClose
  | Rm of (string)
  | Eof
  | Include
  | Setfile
  | NBreak
  | Cend
  | Cbegin of (string)
  | Arg of (string)
  | Bf of (string)
  | Tt of (string)
  | Sf of (string)
  | It of (string)
  | MNormal of (string)
  | Pos of (int)
  | Cal of (string)

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> string
