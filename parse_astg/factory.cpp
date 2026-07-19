#include "factory.h"

#include "graph.h"

namespace parse_astg {

const parse::factory factory(parse::schema::from<graph>());

}

