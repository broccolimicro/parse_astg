#pragma once

#include <parse/parse.h>
#include <parse/syntax.h>
#include <parse_astg/node.h>

namespace parse_astg {

struct arc : parse::syntax {
	arc();
	arc(tokenizer &tokens, std::any data=std::any());
	arc(node n0, node n1);
	~arc();

	vector<node> nodes;

	void parse(tokenizer &tokens, std::any data=std::any());
	static bool is_next(tokenizer &tokens, int i = 1, std::any data=std::any());
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
	parse::syntax *clone() const;
};

}
