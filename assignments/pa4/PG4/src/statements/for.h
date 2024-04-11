#pragma once

#include "../expression.h"
#include "../statement.h"

// For a while loop statement.
class ASTStatementFor : public ASTStatement
{
    // Loop body.
    std::unique_ptr<ASTStatement> body;

    // Initialization function.
    std::unique_ptr<ASTStatement> init;

    // Condition to check.
    std::unique_ptr<ASTExpression> condition;

    // Increment function.
    std::unique_ptr<ASTStatement> incr;

public:

    // Create a new for statement.
    // body: Body of for loop.
    // init: Initialization function.
    // condition: Condition to check.
    // incr: Increment function.
    ASTStatementFor(std::unique_ptr<ASTStatement> body, std::unique_ptr<ASTStatement> init = nullptr, std::unique_ptr<ASTExpression> condition = nullptr, std::unique_ptr<ASTStatement> incr = nullptr) : body(std::move(body)), init(std::move(init)), condition(std::move(condition)), incr(std::move(incr)) {}

    // Create a new for statement.
    // body: Body of for loop.
    // init: Initialization function.
    // condition: Condition to check.
    // incr: Increment function.
    static auto Create(std::unique_ptr<ASTStatement> body, std::unique_ptr<ASTStatement> init = nullptr, std::unique_ptr<ASTExpression> condition = nullptr, std::unique_ptr<ASTStatement> incr = nullptr)
    {
        return std::make_unique<ASTStatementFor>(std::move(body), std::move(init), std::move(condition), std::move(incr));
    }

    // Virtual functions. See base class for details.
    virtual std::unique_ptr<VarType> StatementReturnType(ASTFunction& func) override;
    virtual void Compile(llvm::Module& mod, llvm::IRBuilder<>& builder, ASTFunction& func) override;
    virtual std::string ToString(const std::string& prefix) override;
};