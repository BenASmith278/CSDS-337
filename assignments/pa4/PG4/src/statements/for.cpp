#include "for.h"

#include "../function.h"

std::unique_ptr<VarType> ASTStatementFor::StatementReturnType(ASTFunction& func)
{
    // It is completely possible for a for's condition to never be true, so even if it does return something it's not confirmed.
    // The exception is if the initialization function returns something.
    auto ret = init->StatementReturnType(func);
    if (ret) return std::move(ret);

    return nullptr;
}

void ASTStatementFor::Compile(llvm::Module& mod, llvm::IRBuilder<>& builder, ASTFunction& func)
{
    /*
        A for loop can be desugared to basic blocks. Take the following example:

            for (init(); condition; incr())
            {
                body();
            }

        This is really just another way of saying:
        
            forLoopInit:
                init();
                goto forLoop;

            forLoop:
                if (condition) goto forLoopBody else goto forLoopEnd;

            forLoopBody:
                body();
                incr();
                goto forLoop;

            forLoopEnd:
                ...
    */

    // Create the basic blocks.
    auto* funcVal = (llvm::Function*)func.GetVariableValue(func.name);
    auto forLoop = llvm::BasicBlock::Create(builder.getContext(), "forLoop", funcVal);
    auto forLoopBody = llvm::BasicBlock::Create(builder.getContext(), "forLoopBody", funcVal);
    auto forLoopEnd = llvm::BasicBlock::Create(builder.getContext(), "forLoopEnd", funcVal);

    // if init defined, compile it. Otherwise jump straight to loop body.
    if (init)
        init->Compile(mod, builder, func);
    builder.CreateBr(forLoop);

    // If the condition is defined, then set conditionVal to condition expression. Otherwise, condition is always true.
    builder.SetInsertPoint(forLoop);
    llvm::Value* conditionVal = nullptr;
    if(condition)
        conditionVal = condition->CompileRValue(builder, func);
    else
        conditionVal = llvm::ConstantInt::get(VarTypeSimple::BoolType.GetLLVMType(builder.getContext()), 1);
    builder.CreateCondBr(conditionVal, forLoopBody, forLoopEnd); // If condition is true, go to body. Otherwise, go to end.

    // Compile the body. Only compile the increment statement if it is defined.
    builder.SetInsertPoint(forLoopBody);
    body->Compile(mod, builder, func);
    if (incr)
        incr->Compile(mod, builder, func);
    builder.CreateBr(forLoop);

    // Continue from end of for loop.
    builder.SetInsertPoint(forLoopEnd);
}

std::string ASTStatementFor::ToString(const std::string& prefix)
{
    std::string output = "for\n";
    output += prefix + "├──" + init->ToString(prefix + "│  ");
    output += prefix + "├──" + condition->ToString(prefix + "│  ");
    output += prefix + "├──" + incr->ToString(prefix + "│  ");
    output += prefix + "└──" + body->ToString(prefix + "   ");
    return output;
}