#include "CodaScriptCommands-General.h"
#include "BGSEEConsole.h"

namespace BGSEditorExtender
{
	namespace BGSEEScript
	{
		namespace Commands
		{
			namespace General
			{
				CodaScriptCommandRegistrarDef("General")

				CodaScriptCommandPrototypeDef(Return);
				CodaScriptCommandPrototypeDef(Call);
				CodaScriptCommandPrototypeDef(Break);
				CodaScriptCommandPrototypeDef(Continue);
				CodaScriptCommandPrototypeDef(GetSecondsPassed);
				CodaScriptCommandPrototypeDef(FormatNumber);
				CodaScriptCommandPrototypeDef(PrintToConsole);

				CodaScriptCommandParamData(Return, 1)
				{
					{ "Expression",						ParameterInfo::kType_Multi }
				};

				CodaScriptCommandParamData(FormatNumber, 3)
				{
					{ "Format String",					ICodaScriptDataStore::kDataType_String	},
					{ "Number",							ICodaScriptDataStore::kDataType_Numeric	},
					{ "Interpret As Unsigned Int",		ICodaScriptDataStore::kDataType_Numeric	}
				};

				CodaScriptCommandHandler(Return)
				{
					CodaScriptSyntaxTreeExecuteVisitor* Agent = dynamic_cast<CodaScriptSyntaxTreeExecuteVisitor*>(ExecutionAgent);
					ICodaScriptDataStore* Parameter = NULL;

					CodaScriptCommandExtractArgs(&Parameter);

					SME_ASSERT(Agent && Parameter);

					Agent->SetResult(*dynamic_cast<CodaScriptBackingStore*>(Parameter));
					Agent->SetState(CodaScriptSyntaxTreeExecuteVisitor::kExecutionState_Break);

					return true;
				}

				CodaScriptCommandHandler(Call)
				{
					if (ArgumentCount < 1)
						throw CodaScriptException(ByteCode->GetSource(), "Script name not passed to Call command");
					else if (ArgumentCount > 1 + CodaScriptExecutionContext::kMaxParameters)
						throw CodaScriptException(ByteCode->GetSource(), "Too many arguments passed to Call command - Maximum allowed = %d", CodaScriptExecutionContext::kMaxParameters);

					const char* ScriptName = Arguments[0].GetString();

					CodaScriptBackingStore CallResult(0.0);
					bool ReturnedResult = false;

					CodaScriptMutableDataArrayT PassedParameters;
					for (int i = 1; i < ArgumentCount; i++)
					{
						CodaScriptBackingStore* Store = dynamic_cast<CodaScriptBackingStore*>(&Arguments[i]);
						PassedParameters.push_back(*Store);
					}

					bool ExecuteResult = CODAVM->RunScript(ScriptName, (PassedParameters.size() ? &PassedParameters : NULL), &CallResult, ReturnedResult);
					if (ExecuteResult && ReturnedResult)
						*Result = CallResult;
					else
						*Result = 0.0;

					return true;
				}

				CodaScriptCommandHandler(Break)
				{
					CodaScriptSyntaxTreeExecuteVisitor* Agent = dynamic_cast<CodaScriptSyntaxTreeExecuteVisitor*>(ExecutionAgent);
					SME_ASSERT(Agent);

					ICodaScriptLoopBlock* LoopBlock = Agent->GetCurrentLoop();
					SME_ASSERT(LoopBlock);

					LoopBlock->Break();
					Agent->SetState(CodaScriptSyntaxTreeExecuteVisitor::kExecutionState_Break);
					return true;
				}

				CodaScriptCommandHandler(Continue)
				{
					CodaScriptSyntaxTreeExecuteVisitor* Agent = dynamic_cast<CodaScriptSyntaxTreeExecuteVisitor*>(ExecutionAgent);
					SME_ASSERT(Agent);

					Agent->SetState(CodaScriptSyntaxTreeExecuteVisitor::kExecutionState_Break);
					return true;
				}

				CodaScriptCommandHandler(GetSecondsPassed)
				{
					CodaScriptSyntaxTreeExecuteVisitor* Agent = dynamic_cast<CodaScriptSyntaxTreeExecuteVisitor*>(ExecutionAgent);
					SME_ASSERT(Agent);

					CodaScriptExecutionContext* Context = Agent->GetContext();
					SME_ASSERT(Context);

					*Result = (CodaScriptNumericDataTypeT)Context->GetSecondsPassed();
					return true;
				}

				CodaScriptCommandHandler(FormatNumber)
				{
					CodaScriptStringParameterTypeT FormatString = NULL;
					CodaScriptNumericDataTypeT Number = 0.0, InterpretAsUInt32 = 0.0;

					CodaScriptCommandExtractArgs(&FormatString, &Number, &InterpretAsUInt32);

					char OutBuffer[0x32] = {0};

					if (InterpretAsUInt32)
						sprintf_s(OutBuffer, sizeof(OutBuffer), FormatString, (UInt32)Number);
					else
						sprintf_s(OutBuffer, sizeof(OutBuffer), FormatString, Number);

					*Result = OutBuffer;
					return true;
				}

				CodaScriptCommandHandler(PrintToConsole)
				{
					CodaScriptStringParameterTypeT Message = NULL;

					CodaScriptCommandExtractArgs(&Message);

					BGSEECONSOLE_MESSAGE(Message);
					return true;
				}
			}
		}
	}
}