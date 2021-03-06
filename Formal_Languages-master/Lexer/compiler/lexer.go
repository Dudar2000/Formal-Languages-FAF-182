package lexer

import "Lexer/tokens"


type Lexer struct {
	input        string
	position     int 
	nextPosition int  
	ch           byte 
}

//New function
func New(input string) *Lexer {
	l := &Lexer{input: input}
	l.readChar()
	return l
}

//NextToken fun
func (l *Lexer) NextToken() token.Token {
	var tok token.Token

	l.skipWhitespace()

	switch l.ch {
	case '=':
		tok = newToken(token.EQUAL, l.ch)
	case '-':
		tok = newToken(token.MINUS, l.ch)
	case '/':
		tok = newToken(token.DIVIDE, l.ch)
	case '*':
		tok = newToken(token.MULT, l.ch)
	case '>':
		tok = newToken(token.BIGGER, l.ch)
	case '<':
		tok = newToken(token.LESS, l.ch)
	case ';':
		tok = newToken(token.SEMICOLON, l.ch)
	case '(':
		tok = newToken(token.LPAR, l.ch)
	case ')':
		tok = newToken(token.RPAR, l.ch)
	case ',':
		tok = newToken(token.COMMA, l.ch)
	case '+':
		tok = newToken(token.PLUS, l.ch)
	case '{':
		tok = newToken(token.LBRACK, l.ch)
	case '}':
		tok = newToken(token.RBRACK, l.ch)
	case 0:
		tok.Input = ""
		tok.Type = token.EOF
	default:
		if isLetter(l.ch) {
			tok.Input = l.readIdentifier()
			tok.Type = token.LookupIdent(tok.Input)
			return tok
		} else if isDigit(l.ch) {
			tok.Type = token.INT
			tok.Input = l.readNumber()
			return tok
		} else {
			tok = newToken(token.NEMO, l.ch)
		}
	}
	l.readChar()
	return tok
}

func (l *Lexer) skipWhitespace() {
	for l.ch == ' ' || l.ch == '\t' || l.ch == '\n' || l.ch == '\r' {
		l.readChar()
	}
}

func (l *Lexer) readChar() {
	if l.nextPosition >= len(l.input) {
		l.ch = 0
	} else {
		l.ch = l.input[l.nextPosition]
	}
	l.position = l.nextPosition
	l.nextPosition++
}

func (l *Lexer) readIdentifier() string {
	position := l.position
	for isLetter(l.ch) {
		l.readChar()
	}
	return l.input[position:l.position]
}

func isLetter(ch byte) bool {
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_'
}

func (l *Lexer) readNumber() string {
	position := l.position
	for isDigit(l.ch) {
		l.readChar()
	}
	return l.input[position:l.position]
}

func isDigit(ch byte) bool {
	return '0' <= ch && ch <= '9'
}

func newToken(tokenType token.TokenType, ch byte) token.Token {
	return token.Token{Type: tokenType, Input: string(ch)}
}