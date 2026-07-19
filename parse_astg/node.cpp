#include <parse_astg/node.h>

#include <parse/default/instance.h>
#include <parse/default/symbol.h>
#include <parse/default/number.h>

namespace parse_astg {

node::node() {
	debug_name = "astg_node";
	place = "";
}

node::node(tokenizer &tokens, std::any data) {
	debug_name = "astg_node";
	place = "";
	parse(tokens, data);
}

node::node(expression guard, composition assign, string id) {
	debug_name = "astg_node";
	place = "";
	this->guard = guard;
	this->assign = assign;
	this->id = id;
}

node::node(string place, string id) {
	debug_name = "astg_node";
	this->place = place;
	this->id = id;
}

node::~node() {
}

void node::parse(tokenizer &tokens, std::any data) {
	tokens.syntax_start(this);

	tokens.increment(true);
	string peek = tokens.peek(1);
	bool is_place = (peek.size() > 0 and peek[0] == 'p');
	for (int i = 1; i < (int)peek.size() and is_place; i++)
		if (peek[i] < '0' or peek[i] > '9')
			is_place = false;

	if (peek == "skip")
		tokens.expect("skip");
	else if (is_place)
		tokens.expect<parse::instance>();
	else {
		tokens.expect("skip");
		tokens.expect<composition>();
		tokens.increment(true);
		tokens.expect("->");
		tokens.increment(true);
		tokens.expect<expression>();
	}

	if (tokens.decrement(__FILE__, __LINE__))
	{
		if (tokens.found("skip")) {
			tokens.next();
		} else if (tokens.found<expression>()) {
			guard = expression(tokens, data);

			if (tokens.decrement(__FILE__, __LINE__))
				tokens.next();

			if (tokens.decrement(__FILE__, __LINE__)) {
				if (tokens.found("skip")) {
					tokens.next();
				} else {
					assign = composition(tokens, data);
				}
			}
		} else if (is_place and tokens.found<parse::instance>()) {
			place = tokens.next();
		}

		tokens.increment(false);
		tokens.expect("/");

		if (tokens.decrement(__FILE__, __LINE__)) {
			tokens.next();

			tokens.increment(true);
			tokens.expect<parse::number>();

			if (tokens.decrement(__FILE__, __LINE__))
				id = tokens.next();
		}
	}

	tokens.syntax_end(this);
}

bool node::is_next(tokenizer &tokens, int i, std::any data) {
	return (tokens.is_next("skip") or expression::is_next(tokens, i, data) or parse::instance::is_next(tokens, i, data));
}

void node::register_syntax(tokenizer &tokens) {
	if (!tokens.syntax_registered<node>()) {
		tokens.register_syntax<node>();
		composition::register_syntax(tokens);
		expression::register_syntax(tokens);
		tokens.register_token<parse::instance>();
		tokens.register_token<parse::symbol>();
	}
}

string node::to_string(string tab) const {
	string result = "";
	if (guard.valid and assign.valid) {
		result += guard.to_string(tab) + "->" + assign.to_string(tab);
	} else if (guard.valid) {
		result += guard.to_string(tab) + "->skip";
	} else if (place != "") {
		result += place;
	} else {
		result += "skip";
	}

	if (id != "") {
		result += "/" + id;
	}

	return result;
}

parse::syntax *node::clone() const {
	return new node(*this);
}

}
