//===----------------------------------------------------------------------===//
//                         BusTub
//
// bustub/binder/parser.h
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Copyright 2018-2022 Stichting DuckDB Foundation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice (including the next paragraph)
// shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <string>

#include "binder/bound_statement.h"
#include "binder/simplified_token.h"
#include "binder/tokens.h"
#include "catalog/catalog.h"
#include "catalog/column.h"
#include "nodes/parsenodes.hpp"
#include "pg_definitions.hpp"
#include "postgres_parser.hpp"
#include "type/type_id.h"
#include "type/value.h"

namespace duckdb_libpgquery {
struct PGNode;
struct PGList;
}  // namespace duckdb_libpgquery

namespace bustub {

/**
 * The binder is responsible for transforming the Postgres parse tree to a binder tree
 * which can be recognized unambiguously by the BusTub planner.
 */
class Binder {
 public:
  Binder() = default;

  /** The parsed SQL statements from an invocation to ParseQuery. */
  vector<unique_ptr<BoundStatement>> statements_;

  /** Attempts to parse a query into a series of SQL statements. The parsed statements
   * will be stored in the statements variable.
   */
  void ParseAndBindQuery(const string &query, const Catalog &catalog);

  /** Returns true if the given text matches a keyword of the parser */
  static auto IsKeyword(const string &text) -> bool;

  /** Returns a list of all keywords in the parser */
  static auto KeywordList() -> vector<ParserKeyword>;

  /** Tokenize a query, returning the raw tokens together with their locations */
  static auto Tokenize(const string &query) -> vector<SimplifiedToken>;

  /** Transforms a Postgres parse tree into a set of SQL Statements */
  auto TransformParseTree(const Catalog &catalog, duckdb_libpgquery::PGList *tree) const
      -> std::vector<std::unique_ptr<BoundStatement>>;

  /** Transforms a Postgres statement into a single SQL statement */
  auto TransformStatement(const Catalog &catalog, duckdb_libpgquery::PGNode *stmt) const -> unique_ptr<BoundStatement>;

  /** Get the string of a Postgres node type */
  static auto NodetypeToString(duckdb_libpgquery::PGNodeTag type) -> string;
};

}  // namespace bustub
