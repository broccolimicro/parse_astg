#include "expression.h"
#include <parse_expression/precedence.h>
#include <parse_expression/literal.h>
#include <parse/wrapper.h>

namespace parse_astg {

std::shared_ptr<parse_expression::config> expression_config::cfg = 
	std::make_shared<parse_expression::config>(parse_astg::makeExprConfig());

expression_config::expression_config() {
	debug_name = "astg";
}

expression_config::~expression_config() {
}

std::shared_ptr<parse_expression::config> composition_config::cfg = 
	std::make_shared<parse_expression::config>(parse_astg::makeCompConfig());

composition_config::composition_config() {
	debug_name = "astg";
}

composition_config::~composition_config() {
}

parse_expression::config makeExprConfig() {
	parse_expression::config cfg;
	int CONSTANT = cfg.push<constant>("constant");
	int LITERAL = cfg.push<literal>("literal");
	int LABEL = cfg.push<label>("label");
	int IDENT = cfg.push<ident>("ident");

	cfg.base = {LITERAL, CONSTANT};

	using operation_set=parse_expression::operation_set;

	/*cfg.order.push(operation_set::TERNARY);
	cfg.order.push_back("", "?", ":", "");*/

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "|", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "&", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "^", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "||", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "&&", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "^^", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "==", "");
	cfg.order.push_back("", "", "!=", "");
	cfg.order.push_back("", "", "<", "");
	cfg.order.push_back("", "", ">", "");
	cfg.order.push_back("", "", "<=", "");
	cfg.order.push_back("", "", ">=", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "<<", "");
	cfg.order.push_back("", "", ">>", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "+", "");
	cfg.order.push_back("", "", "-", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", "*", "");
	cfg.order.push_back("", "", "/", "");
	cfg.order.push_back("", "", "%", "");

	cfg.order.push(operation_set::UNARY);
	cfg.order.push_back("!", "", "", "");
	cfg.order.push_back("~", "", "", "");
	cfg.order.push_back("+", "", "", "");
	cfg.order.push_back("-", "", "", "");
	cfg.order.push_back("?", "", "", "");

	cfg.set_lvalue();

	cfg.order.push(operation_set::MODIFIER);
	cfg.order.push_back("", "'", "", "", {IDENT});

	cfg.order.push(operation_set::MODIFIER);
	//cfg.order.push_back("", "{", ",", "}");
	cfg.order.push_back("", "(", ",", ")");
	cfg.order.push_back("", ".", "", "", {LABEL});
	cfg.order.push_back("", "[", ":", "]");

	/*cfg.order.push(operation_set::MODIFIER);
	cfg.order.push_back("", "::", "", "", {LABEL});*/

	cfg.order.push(operation_set::GROUP);
	cfg.order.push_back("[", "", ",", "]");

	return cfg;
}

parse_expression::config makeCompConfig() {
	parse_expression::config cfg;

	int GUARD = cfg.push<guard>("guard");
	int ASSIGN = cfg.push<assignment>("assign");

	cfg.base = {GUARD, ASSIGN};

	using operation_set=parse_expression::operation_set;

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", ":", "");

	cfg.order.push(operation_set::BINARY);
	cfg.order.push_back("", "", ",", "");

	cfg.set_lvalue();

	return cfg;
}

}
