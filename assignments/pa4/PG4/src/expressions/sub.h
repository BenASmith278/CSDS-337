#pragma once

#include "../expression.h"

// An expression that subtracts two operands
class ASTExpressionSubtraction : public ASTExpression
{
    // Operands to work with
    std::unique_ptr<ASTExpression> s1;
    std::unique_ptr<ASTExpression> s2;

    // Return type to cache.
    VarTypeSimple* returnType = nullptr;

public:

    // Create a new subtraction expression
    // s1: Left side expression of the subtraction statement.
    // s2: Right side expression of the subtraction statement.
    ASTExpressionSubtraction(std::unique_ptr<ASTExpression> s1, std::unique_ptr<ASTExpression> s2) : s1(std::move(s1)), s2(std::move(s2)) {}

    // Create a new subtraction expression.
    // s1 Left side expression of the subtraction statement.
    // s2 Right side expression of the subtraction statement.
    static auto Create(std::unique_ptr<ASTExpression> s1, std::unique_ptr<ASTExpression> s2)
    {
        return std::make_unique<ASTExpressionSubtraction>(std::move(s1), std::move(s2));
    }

    // Virtual functions. See base class for details.
    std::unique_ptr<VarType> ReturnType(ASTFunction& func) override;
    bool IsLValue(ASTFunction& func) override;
    llvm::Value* Compile(llvm::IRBuilder<>& builder, ASTFunction& func) override;
    std::string ToString(const std::string& prefix) override;
};