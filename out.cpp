// Generated by llvm2cpp - DO NOT MODIFY!

#include <llvm/Pass.h>
#include <llvm/PassManager.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <algorithm>
using namespace llvm;

Module* makeLLVMModule();

int main(int argc, char**argv) {
  Module* Mod = makeLLVMModule();
  verifyModule(*Mod, PrintMessageAction);
  PassManager PM;
  PM.add(createPrintModulePass(&outs()));
  PM.run(*Mod);
  return 0;
}


Module* makeLLVMModule() {
 // Module Construction
 Module* mod = new Module("back.ll", getGlobalContext());
 mod->setDataLayout("0x1076710");
 mod->setTargetTriple("x86_64-unknown-linux-gnu");

 // Type Definitions
 ArrayType* ArrayTy_0 = ArrayType::get(IntegerType::get(mod->getContext(), 8), 17);

 PointerType* PointerTy_1 = PointerType::get(ArrayTy_0, 0);

 std::vector<Type*>FuncTy_2_args;
 PointerType* PointerTy_3 = PointerType::get(IntegerType::get(mod->getContext(), 8), 0);

 FuncTy_2_args.push_back(PointerTy_3);
 FunctionType* FuncTy_2 = FunctionType::get(
  /*Result=*/Type::getVoidTy(mod->getContext()),
  /*Params=*/FuncTy_2_args,
  /*isVarArg=*/false);

 PointerType* PointerTy_4 = PointerType::get(PointerTy_3, 0);

 std::vector<Type*>FuncTy_5_args;
 FunctionType* FuncTy_5 = FunctionType::get(
  /*Result=*/IntegerType::get(mod->getContext(), 32),
  /*Params=*/FuncTy_5_args,
  /*isVarArg=*/false);

 PointerType* PointerTy_6 = PointerType::get(FuncTy_2, 0);


 // Function Declarations

 Function* func__Z15DoStuffWithCStrPKc = mod->getFunction("_Z15DoStuffWithCStrPKc");
 if (!func__Z15DoStuffWithCStrPKc) {
 func__Z15DoStuffWithCStrPKc = Function::Create(
  /*Type=*/FuncTy_2,
  /*Linkage=*/GlobalValue::ExternalLinkage,
  /*Name=*/"_Z15DoStuffWithCStrPKc", mod);
 func__Z15DoStuffWithCStrPKc->setCallingConv(CallingConv::C);
 }
 AttributeSet func__Z15DoStuffWithCStrPKc_PAL;
 {
  SmallVector<AttributeSet, 4> Attrs;
  AttributeSet PAS;
   {
    AttrBuilder B;
    B.addAttribute(Attribute::NoUnwind);
    B.addAttribute(Attribute::UWTable);
    PAS = AttributeSet::get(mod->getContext(), ~0U, B);
   }

  Attrs.push_back(PAS);
  func__Z15DoStuffWithCStrPKc_PAL = AttributeSet::get(mod->getContext(), Attrs);

 }
 func__Z15DoStuffWithCStrPKc->setAttributes(func__Z15DoStuffWithCStrPKc_PAL);

 Function* func_main = mod->getFunction("main");
 if (!func_main) {
 func_main = Function::Create(
  /*Type=*/FuncTy_5,
  /*Linkage=*/GlobalValue::ExternalLinkage,
  /*Name=*/"main", mod);
 func_main->setCallingConv(CallingConv::C);
 }
 AttributeSet func_main_PAL;
 {
  SmallVector<AttributeSet, 4> Attrs;
  AttributeSet PAS;
   {
    AttrBuilder B;
    B.addAttribute(Attribute::NoUnwind);
    B.addAttribute(Attribute::UWTable);
    PAS = AttributeSet::get(mod->getContext(), ~0U, B);
   }

  Attrs.push_back(PAS);
  func_main_PAL = AttributeSet::get(mod->getContext(), Attrs);

 }
 func_main->setAttributes(func_main_PAL);

 // Global Variable Declarations


 GlobalVariable* gvar_array__str = new GlobalVariable(/*Module=*/*mod,
 /*Type=*/ArrayTy_0,
 /*isConstant=*/true,
 /*Linkage=*/GlobalValue::PrivateLinkage,
 /*Initializer=*/0, // has initializer, specified below
 /*Name=*/".str");
 gvar_array__str->setAlignment(1);

 // Constant Definitions
 Constant *const_array_7 = ConstantDataArray::getString(mod->getContext(), "This is a string", true);
 ConstantInt* const_int32_8 = ConstantInt::get(mod->getContext(), APInt(32, StringRef("1"), 10));
 std::vector<Constant*> const_ptr_9_indices;
 ConstantInt* const_int32_10 = ConstantInt::get(mod->getContext(), APInt(32, StringRef("0"), 10));
 const_ptr_9_indices.push_back(const_int32_10);
 const_ptr_9_indices.push_back(const_int32_10);
 Constant* const_ptr_9 = ConstantExpr::getGetElementPtr(gvar_array__str, const_ptr_9_indices);

 // Global Variable Definitions
 gvar_array__str->setInitializer(const_array_7);

 // Function Definitions

 // Function: _Z15DoStuffWithCStrPKc (func__Z15DoStuffWithCStrPKc)
 {
  Function::arg_iterator args = func__Z15DoStuffWithCStrPKc->arg_begin();
  Value* ptr_msg = args++;
  ptr_msg->setName("msg");

  BasicBlock* label_11 = BasicBlock::Create(mod->getContext(), "",func__Z15DoStuffWithCStrPKc,0);

  // Block  (label_11)
  AllocaInst* ptr_12 = new AllocaInst(PointerTy_3, "", label_11);
  ptr_12->setAlignment(8);
  StoreInst* void_13 = new StoreInst(ptr_msg, ptr_12, false, label_11);
  void_13->setAlignment(8);
  ReturnInst::Create(mod->getContext(), label_11);

 }

 // Function: main (func_main)
 {

  BasicBlock* label_15 = BasicBlock::Create(mod->getContext(), "",func_main,0);

  // Block  (label_15)
  CallInst* void_16 = CallInst::Create(func__Z15DoStuffWithCStrPKc, const_ptr_9, "", label_15);
  void_16->setCallingConv(CallingConv::C);
  void_16->setTailCall(false);
  AttributeSet void_16_PAL;
  void_16->setAttributes(void_16_PAL);

  ReturnInst::Create(mod->getContext(), const_int32_10, label_15);

 }

 return mod;
}
