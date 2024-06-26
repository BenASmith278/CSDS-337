#include "and.h"

#include "../function.h"

std::unique_ptr<VarType> ASTExpressionAnd::ReturnType(ASTFunction& func)
{
    return VarTypeSimple::BoolType.Copy(); // a && b is always a boolean.
}

bool ASTExpressionAnd::IsLValue(ASTFunction& func)
{
    return false; // && operator works on two R-Values to produce an R-Value.
}

llvm::Value* ASTExpressionAnd::Compile(llvm::IRBuilder<>& builder, ASTFunction& func)
{
    // Make sure to cast both sides as booleans first.
    ASTExpression::ImplicitCast(func, a1, &VarTypeSimple::BoolType);
    ASTExpression::ImplicitCast(func, a2, &VarTypeSimple::BoolType);

    // Create blocks. Check right is if left is true. Continue block happens if false.
    auto* funcVal = (llvm::Function*)func.GetVariableValue(func.name);
    llvm::BasicBlock* checkRight = llvm::BasicBlock::Create(builder.getContext(), "checkRight", funcVal);
    llvm::BasicBlock* cont = llvm::BasicBlock::Create(builder.getContext(), "cont", funcVal);

    // If left is true, then we need to check right. Otherwise branch to the continue block where we know the final result will be set as false.
    llvm::Value* tmp = a1->CompileRValue(builder, func);
    builder.CreateCondBr(tmp, checkRight, cont); // If left value is true, we branch to checking the right one, else continue.

    // Compile the right expression if needed.
    builder.SetInsertPoint(checkRight);
    tmp = a2->CompileRValue(builder, func);
    builder.CreateBr(cont);
    
    // tmp holds truthyness of operation.
    builder.SetInsertPoint(cont);
    return tmp;
}

std::string ASTExpressionAnd::ToString(const std::string& prefix)
{
    std::string ret = "(&&)\n";
    ret += prefix + "├──" + a1->ToString(prefix + "│  ");
    ret += prefix + "└──" + a2->ToString(prefix + "   ");
    return ret;
}