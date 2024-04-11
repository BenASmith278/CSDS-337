#pragma once

#include "../expression.h"

// An expression that divides two operands.
class ASTExpressionDivision : public ASTExpression
{
    // Operands to work with.
    std::unique_ptr<ASTExpression> d1;
    std::unique_ptr<ASTExpression> d2;

    // Return type to cache.
    VarTypeSimple* returnType = nullptr;

public:
    
    // Create a new division expression.
    // d1: Left side of expression of the division statement.
    // d2: Right side of expression of the division statement.
    ASTExpressionDivision(std::unique_ptr<ASTExpression> d1, std::unique_ptr<ASTExpression> d2) : d1(std::move(d1)), d2(std::move(d2)) {}

    // Create a new division expression.
    // d1: Left side of expression of the division statement.
    // d2: Right side of expression of the division statement.
    static auto Create(std::unique_ptr<ASTExpression> d1, std::unique_ptr<ASTExpression> d2)
    {
        return std::make_unique<ASTExpressionDivision>(std::move(d1), std::move(d2));
    }

    // Virtual functions. See base class for details.
    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
};