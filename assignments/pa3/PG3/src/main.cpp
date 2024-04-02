#include <iostream>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

using namespace llvm;

// Starter code for the assignment.
int main()
{
    // Step 1 - Setup LLVM module. Note exporting is continued below.
    LLVMContext context; // Our base context. This is how we talk to LLVM.
    // TODO: CREATE MODULE HERE!!!
    Module mod("sampleMod", context); // Create a new module.
    IRBuilder<> builder(context);
    std::string error;
    raw_string_ostream errorStream(error);

    // SIMPLE
    Function *simple = Function::Create(
        FunctionType::get(Type::getInt32Ty(context), false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "simple",
        &mod);

    BasicBlock *simpleEntry = BasicBlock::Create(context, "entry", simple);

    builder.SetInsertPoint(simpleEntry);
    builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), 0));

    bool valid = verifyFunction(*simple, &errorStream);

    // ADD
    Function *add = Function::Create(
        FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context)}, false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "add",
        &mod);

    BasicBlock *addEntry = BasicBlock::Create(context, "entry", add);

    builder.SetInsertPoint(addEntry);
    builder.CreateRet(builder.CreateAdd(add->getArg(0), add->getArg(1)));

    valid = valid || verifyFunction(*add, &errorStream);

    // ADDINTFLOAT
    Function *addIntFloat = Function::Create(
        FunctionType::get(Type::getFloatTy(context), {Type::getInt32Ty(context), Type::getFloatTy(context)}, false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "addIntFloat",
        &mod);

    BasicBlock *addIFEntry = BasicBlock::Create(context, "entry", addIntFloat);

    builder.SetInsertPoint(addIFEntry);
    builder.CreateRet(builder.CreateFAdd(builder.CreateSIToFP(addIntFloat->getArg(0), Type::getFloatTy(context)), addIntFloat->getArg(1)));

    valid = valid || verifyFunction(*addIntFloat, &errorStream);

    // CONDITIONAL
    Function *conditional = Function::Create(
        FunctionType::get(Type::getInt32Ty(context), {Type::getInt1Ty(context)}, false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "conditional",
        &mod);

    BasicBlock *conditionalEntry = BasicBlock::Create(context, "entry", conditional);
    BasicBlock *conditionalTrue = BasicBlock::Create(context, "doThen", conditional);
    BasicBlock *conditionalFalse = BasicBlock::Create(context, "doElse", conditional);
    BasicBlock *conditionalContinue = BasicBlock::Create(context, "doContinue", conditional);

    builder.SetInsertPoint(conditionalEntry);
    Value *condAlloca = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "condAlloca");
    builder.CreateCondBr(conditional->getArg(0), conditionalTrue, conditionalFalse);

    builder.SetInsertPoint(conditionalTrue);
    builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 3), condAlloca);
    builder.CreateBr(conditionalContinue);

    builder.SetInsertPoint(conditionalFalse);
    builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 5), condAlloca);
    builder.CreateBr(conditionalContinue);

    builder.SetInsertPoint(conditionalContinue);
    builder.CreateRet(builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(context), 11), builder.CreateLoad(Type::getInt32Ty(context), condAlloca)));

    valid = valid || verifyFunction(*conditional, &errorStream);

    // ONETWOPHI
    Function *oneTwoPhi = Function::Create(
        FunctionType::get(Type::getInt32Ty(context), {Type::getInt1Ty(context)}, false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "oneTwoPhi",
        &mod);

    BasicBlock *otpEntry = BasicBlock::Create(context, "entry", oneTwoPhi);
    BasicBlock *otpTrue = BasicBlock::Create(context, "doThen", oneTwoPhi);
    BasicBlock *otpFalse = BasicBlock::Create(context, "doElse", oneTwoPhi);
    BasicBlock *otpContinue = BasicBlock::Create(context, "doContinue", oneTwoPhi);

    builder.SetInsertPoint(otpEntry);
    Value *otpAlloca = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "otpAlloca");
    builder.CreateCondBr(oneTwoPhi->getArg(0), otpTrue, otpFalse);

    builder.SetInsertPoint(otpTrue);
    builder.CreateBr(otpContinue);

    builder.SetInsertPoint(otpFalse);
    builder.CreateBr(otpContinue);

    builder.SetInsertPoint(otpContinue);
    PHINode *otpPhi = builder.CreatePHI(Type::getInt32Ty(context), 2, "otpPhi");
    otpPhi->addIncoming(ConstantInt::get(Type::getInt32Ty(context), 3), otpTrue);
    otpPhi->addIncoming(ConstantInt::get(Type::getInt32Ty(context), 5), otpFalse);
    Value *otpPhiVal = otpPhi;
    builder.CreateRet(builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(context), 11), otpPhiVal));

    valid = valid || verifyFunction(*oneTwoPhi, &errorStream);

    // SELECTION
    Function *selection = Function::Create(
        FunctionType::get(Type::getInt32Ty(context), {Type::getInt1Ty(context)}, false),
        GlobalValue::LinkageTypes::ExternalLinkage,
        "selection",
        &mod);

    BasicBlock *selectEntry = BasicBlock::Create(context, "entry", selection);

    builder.SetInsertPoint(selectEntry);
    Value *selAlloca = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "selAlloca");
    Value *selVal = builder.CreateSelect(selection->getArg(0), ConstantInt::get(Type::getInt32Ty(context), 3), ConstantInt::get(Type::getInt32Ty(context), 5));
    builder.CreateStore(selVal, selAlloca);
    builder.CreateRet(builder.CreateAdd(ConstantInt::get(Type::getInt32Ty(context), 11), builder.CreateLoad(Type::getInt32Ty(context), selAlloca)));

    valid = valid || verifyFunction(*selection, &errorStream);

    // PROBLEM 8
    legacy::FunctionPassManager passMan(&mod);
    passMan.add(createPromoteMemoryToRegisterPass());
    passMan.add(createReassociatePass());
    passMan.add(createGVNPass());
    passMan.add(createCFGSimplificationPass());

    for (Function &F : mod)
        passMan.run(F);

    passMan.doFinalization();

    // Step 1 - Export LLVM module.
    std::error_code err;                       // Error code from outstream, we can reuse this.
    raw_fd_ostream outLl("sampleMod.ll", err); // Open an output file.
    mod.print(outLl, nullptr);                 // Print LLVM assembly to the file.
    outLl.close();                             // Close file to save resources.
    // TODO: WRITE THE .BC FILE HERE!!!
    raw_fd_ostream outBc("sampleMod.bc", err);
    WriteBitcodeToFile(mod, outBc);
    outBc.close();

    errs() << errorStream.str();

    return valid;
}
