#include "factory.h"

#include "graph.h"

namespace parse_astg {

parse::syntax *produce(tokenizer &tokens, void *data) {
	return new graph(tokens, data);
}

void expect(tokenizer &tokens) {
	tokens.expect<graph>();
}

void register_syntax(tokenizer &tokens) {
	graph::register_syntax(tokens);
}

const parse::factory factory(register_syntax, expect, produce);

}

