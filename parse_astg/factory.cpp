#include "factory.h"

#include "graph.h"
#include <parse_expression/precedence.h>

namespace parse_astg {

parse::syntax *produce(tokenizer &tokens, void *data) {
	return new graph(tokens, data);
}

void expect(tokenizer &tokens) {
	tokens.expect<graph>();
}

void setup_expressions() {
	parse_expression::precedence_set result;
	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "|", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "&", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "^", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "==", "");
	result.push_back("", "", "~=", "");
	result.push_back("", "", "<", "");
	result.push_back("", "", ">", "");
	result.push_back("", "", "<=", "");
	result.push_back("", "", ">=", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "||", "");
	
	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "&&", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "^^", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "<<", "");
	result.push_back("", "", ">>", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "+", "");
	result.push_back("", "", "-", "");

	result.push(parse_expression::operation_set::BINARY);
	result.push_back("", "", "*", "");
	result.push_back("", "", "/", "");
	result.push_back("", "", "%", "");

	result.push(parse_expression::operation_set::UNARY);
	result.push_back("!", "", "", "");
	result.push_back("~", "", "", "");
	result.push_back("(bool)", "", "", "");
	result.push_back("+", "", "", "");
	result.push_back("-", "", "", "");

	result.push(parse_expression::operation_set::MODIFIER);
	result.push_back("", "!", "", "");
	
	result.push(parse_expression::operation_set::UNARY);
	result.push_back("#", "", "", "");
	result.push_back("", "", "", "?");

	result.push(parse_expression::operation_set::MODIFIER);
	result.push_back("", "'", "", "");

	result.push(parse_expression::operation_set::MODIFIER);
	result.push_back("", "(", ",", ")");
	result.push_back("", ".", "", "");
	result.push_back("", "[", ":", "]");
	
	result.push(parse_expression::operation_set::MODIFIER);
	result.push_back("", "::", "", "");
	parse_expression::expression::register_precedence(result);
	parse_expression::assignment::lvalueLevel = 11;
}

void register_syntax(tokenizer &tokens) {
	setup_expressions();
	graph::register_syntax(tokens);
}

}

