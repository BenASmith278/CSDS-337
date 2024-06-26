#include "negative.h"

std::unique_ptr<VarType> ASTExpressionNegation::ReturnType(ASTFunction& func)
{
    return std::make_unique<VarTypeSimple>(*returnType);
}

bool ASTExpressionNegation::IsLValue(ASTFunction& func)
{
    return false; // Even if negating a variable we need to load from it first to negate its raw value.
}

llvm::Value* ASTExpressionNegation::Compile(llvm::IRBuilder<>& builder, ASTFunction& func)
{
    auto retType = ReturnType(func);
    // Negate should invert numbers and also serve as a logical not
    if (retType->Equals(&VarTypeSimple::FloatType))
        return builder.CreateFMul(operand->CompileRValue(builder, func), llvm::ConstantFP::get(VarTypeSimple::FloatType.GetLLVMType(builder.getContext()), llvm::APFloat(-1.0)));
    else if (retType->Equals(&VarTypeSimple::IntType))
        return builder.CreateMul(operand->CompileRValue(builder, func), llvm::ConstantInt::get(VarTypeSimple::IntType.GetLLVMType(builder.getContext()), -1));
    else if (retType->Equals(&VarTypeSimple::BoolType))
        return builder.CreateNot(operand->CompileRValue(builder, func));
    else
        throw std::runtime_error("ERROR: Expected number or boolean operand in negation but got another type instead.");
}

std::string ASTExpressionNegation::ToString(const std::string& prefix)
{
    return "!\n" + prefix + "└──" + operand->ToString(prefix + "  ");
}