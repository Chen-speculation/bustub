//===----------------------------------------------------------------------===//
//                         BusTub
//
// binder/delete_statement.h
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>

#include "binder/binder.h"

namespace bustub {

class DeleteStatement : public BoundStatement {
 public:
  explicit DeleteStatement(duckdb_libpgquery::PGDeleteStmt *pg_stmt);

  string table_;

  auto ToString() const -> string override;
};

}  // namespace bustub
