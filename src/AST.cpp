#include "AST.hpp"

ASTBlock global_defaultGlobalScope;
ASTDefinition* global_voidType;
ASTDefinition* global_S32Type;
ASTDefinition* global_F32Type;

void InitalizeLanguagePrimitives(ASTBlock* scope, llvm::Module* module) {
	global_voidType = CreateType(scope, "Void", llvm::Type::getVoidTy(module->getContext()));

	CreateType(scope, "S8", llvm::Type::getInt8Ty(module->getContext()));
	CreateType(scope, "S16", llvm::Type::getInt16Ty(module->getContext()));
	global_S32Type = CreateType(scope, "S32", llvm::Type::getInt32Ty(module->getContext()));
	CreateType(scope, "S64", llvm::Type::getInt64Ty(module->getContext()));

	CreateType(scope, "F16", llvm::Type::getHalfTy(module->getContext()));
	global_F32Type = CreateType(scope, "F32", llvm::Type::getFloatTy(module->getContext()));
	CreateType(scope, "F64", llvm::Type::getDoubleTy(module->getContext()));
	CreateType(scope, "F128", llvm::Type::getFP128Ty(module->getContext()));
}

ASTDefinition* CreateType(ASTBlock* scope, const std::string& name, llvm::Type* type) {
	auto typeDefn = new ASTDefinition;
	typeDefn->nodeType = AST_DEFINITION;
	typeDefn->llvmType = type;
	auto identifier = CreateIdentifier(scope, name);
	identifier->node = typeDefn;
	return typeDefn;
}

global_variable std::unordered_map<std::string, ASTIdentifier*> global_identifierLookupMap;
global_variable ASTIdentifier global_identifiers[1024];
global_variable U32 global_identifierCount = 0;

ASTIdentifier* CreateIdentifier(const std::string& name) {
	auto result = &global_identifiers[global_identifierCount++];
	global_identifierLookupMap[name] = result;
	result->name = name;
	return result;
}

ASTIdentifier* CreateIdentifier(ASTBlock* scope, const Token& token) {
	auto result = &global_identifiers[global_identifierCount++];
	global_identifierLookupMap[token.string] = result;
	result->site = token.site;
	result->name = token.string;
	scope->identifiers[token.string] = result;
	return result;
}

ASTIdentifier* CreateIdentifier(ASTBlock* scope, const std::string& name) {
	auto result = &global_identifiers[global_identifierCount++];
	global_identifierLookupMap[name] = result;
	result->name = name;
	scope->identifiers[name] = result;
	return result;
}

ASTIdentifier* FindIdentifier(const std::string& name) {
	auto result = global_identifierLookupMap[name];
	return result;
}

ASTIdentifier* FindIdentifier(ASTBlock* block, const Token& token) {
	auto result = global_identifierLookupMap[token.string];
	return result;
}

ASTIdentifier* FindIdentifier(ASTBlock* block, const std::string& name) {
	auto result = block->identifiers[name];
	if (!result && block->parent != nullptr)
		result = FindIdentifier(block->parent, name);
	return result;
}

ASTBinaryOperation* CreateBinaryOperation(TokenType binop, ASTExpression* lhs, ASTExpression* rhs) {
	auto result = new ASTBinaryOperation();
	result->nodeType = AST_BINOP;
	result->binop = binop;
	//HACK
	//Reduntant error checking for the purposes of the HACK
	if(lhs->type != rhs->type) {
		LOG_ERROR("BINOP fail");
	}
	result->type = lhs->type;
	result->lhs = lhs;
	result->rhs = rhs;
	return result;
}

ASTStruct* CreateStruct() {
	auto result = new ASTStruct;
	result->nodeType = AST_STRUCT;
	return result;
}

ASTMemberAccess* CreateMemberAccess(ASTVariable* structVar) {
	auto result = new ASTMemberAccess;
	result->nodeType = AST_MEMBER_ACCESS;
	result->structVar = structVar;
	return result;
}

ASTMemberAccess* CreateMemberAccess(ASTVariable* structVar, U32 index, AccessMode mode) {
	auto result = new ASTMemberAccess;
	result->nodeType = AST_MEMBER_ACCESS;
	result->structVar = structVar;
	result->mode = mode;
	return result;
}

ASTMemberExpr* CreateMemberExpr(ASTVariable* structVar, U32 memberIndex) {
	auto result = new ASTMemberExpr();
	result->nodeType = AST_MEMBER_EXPR;
	result->structVar = structVar;

	auto structDefn = (ASTStruct*)structVar->type;
	auto memberType = structDefn->memberTypes[memberIndex];
	result->type = memberType;
	return result;
}


ASTMemberExpr* CreateMemberExpr(ASTVariable* structVar) {
	auto result = new ASTMemberExpr();
	result->nodeType = AST_MEMBER_EXPR;
	result->structVar = structVar;
	auto structDefn = (ASTStruct*)structVar->type;
	return result;
}


S32 GetMemberIndex(ASTStruct* structDefn, const std::string& memberName) {
	for (auto i = 0; i < structDefn->memberNames.size(); i++) {
		auto& structMemberName = structDefn->memberNames[i];
		if (!structMemberName.compare(memberName)) {
			return i;
		}
	}
	return -1;
}

ASTVarExpr* CreateVarExpr(ASTVariable* var) {
	auto result = new ASTVarExpr;
	result->nodeType = AST_VAR_EXPR;
	result->var = var;
	return result;
}

ASTFunction* CreateFunction(ASTBlock* block) {
	ASTFunction* function = new ASTFunction;
	function->nodeType = AST_FUNCTION;
	function->parent = block;
	block->members.push_back(function);
	return function;
}

ASTCall* CreateCall() {
	ASTCall* call = new ASTCall;
	call->nodeType = AST_CALL;
	return call;
}

ASTBlock* CreateBlock(ASTBlock* block) {
	auto result = new ASTBlock();
	result->depth = (block == nullptr) ? 0 : block->depth + 1;
	result->parent = block;
	result->nodeType = AST_BLOCK;
	return result;
}

ASTReturn* CreateReturnValue(ASTExpression* value) {
	auto result = new ASTReturn();
	result->nodeType = AST_RETURN;
	result->value = value;
	return result;
}

ASTIntegerLiteral* CreateIntegerLiteral(S64 value) {
	auto result = new ASTIntegerLiteral();
	result->nodeType = AST_INTEGER_LITERAL;
	result->type = (ASTDefinition*)global_S32Type;
	result->value = value;
	return result;
}

ASTFloatLiteral* CreateFloatLiteral(F64 value) {
	auto result = new ASTFloatLiteral();
	result->nodeType = AST_FLOAT_LITERAL;
	result->type = (ASTDefinition*)global_F32Type;
	result->value = value;
	return result;
}

ASTVariable* CreateVariable(ASTBlock* block) {
	auto result = new ASTVariable;
	result->nodeType = AST_VARIABLE;
	result->block = block;
	result->allocaInst = nullptr;
	return result;
}

// This is just analogous for a store
// Why do we need to use this notation / jargon
ASTMutation* CreateMutation(ASTVariable* variable, ASTExpression* expr) {
	auto result = new ASTMutation();
	result->nodeType = AST_MUTATION;
	result->variable = variable;
	result->value = expr;
	return result;
}

// Control flow
ASTIfStatement* CreateIfStatement(ASTExpression* expr) {
	auto result = new ASTIfStatement;
	result->nodeType = AST_IF;
	result->expr = expr;
	result->ifBlock = nullptr;
	result->elseBlock = nullptr;
	return result;
}

ASTIter* CreateIter(ASTIdentifier* ident, ASTExpression* start, ASTExpression* end, ASTExpression* step, ASTBlock* body) {
	auto result = new ASTIter;
	result->nodeType = AST_ITER;
	result->varIdent = ident;
	result->start = start;
	result->end = end;
	result->step = step;
	result->body = body;
	return result;
}

std::string ToString(ASTNodeType nodeType) {
	switch(nodeType) {
	case AST_IDENTIFIER: return "Identifier";
	default: return "Too Lazy to implement ToString for this identifier";
	}
}
