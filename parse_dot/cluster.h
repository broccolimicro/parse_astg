/*
 * cluster.h
 *
 *  Created on: Feb 3, 2014
 *      Author: nbingham
 */

#include "graph.h"

#include <parse/parse.h>
#include <parse/syntax.h>

#ifndef parse_dot_cluster_h
#define parse_dot_cluster_h

namespace parse_dot
{
struct cluster : parse::syntax
{
	cluster();
	cluster(configuration &config, tokenizer &tokens);
	~cluster();

	vector<graph> graphs;

	void parse(configuration &config, tokenizer &tokens);
	static bool is_next(configuration &config, tokenizer &tokens, int i = 1);
	static void register_syntax(tokenizer &tokens);

	string to_string(string tab = "") const;
};
}

#endif