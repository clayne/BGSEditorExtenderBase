#include "CodaScriptCommands-Array.h"
#include "CodaUtilities.h"

namespace bgsee
{
	namespace script
	{
		namespace commands
		{
			namespace array
			{
				CodaScriptCommandRegistrarDef("Array")

				CodaScriptCommandPrototypeDef(ArrayCreate);
				CodaScriptCommandPrototypeDef(ArrayInsert);
				CodaScriptCommandPrototypeDef(ArrayErase);
				CodaScriptCommandPrototypeDef(ArrayClear);
				CodaScriptCommandPrototypeDef(ArraySize);
				CodaScriptCommandPrototypeDef(ArrayInsertAt);
				CodaScriptCommandPrototypeDef(ArraySetAt);
				CodaScriptCommandPrototypeDef(ArrayAppend);

				CodaScriptCommandParamData(ArrayInsert, 3)
				{
					{ "Array",								ICodaScriptDataStore::kDataType_Array	},
					{ "Element",							ParameterInfo::kType_Multi				},
					{ "Index",								ICodaScriptDataStore::kDataType_Numeric	}
				};

				CodaScriptCommandParamData(ArrayErase, 2)
				{
					{ "Array",								ICodaScriptDataStore::kDataType_Array	},
					{ "Index",								ICodaScriptDataStore::kDataType_Numeric	}
				};

				CodaScriptCommandParamData(ArrayInsertAt, 3)
				{
					{ "Array",								ICodaScriptDataStore::kDataType_Array	},
					{ "Element",							ParameterInfo::kType_Multi				},
					{ "Index",								ICodaScriptDataStore::kDataType_Numeric	}
				};

				CodaScriptCommandParamData(ArraySetAt, 3)
				{
					{ "Array",								ICodaScriptDataStore::kDataType_Array	},
					{ "Element",							ParameterInfo::kType_Multi				},
					{ "Index",								ICodaScriptDataStore::kDataType_Numeric	}
				};

				CodaScriptCommandParamData(ArrayAppend, 2)
				{
					{ "Array",								ICodaScriptDataStore::kDataType_Array	},
					{ "Element",							ParameterInfo::kType_Multi				}
				};

				CodaScriptCommandHandler(ArrayCreate)
				{
					CodaScriptNumericDataTypeT Size = 0;

					CodaScriptCommandExtractArgs(&Size);

					if (Size < 5)
						Size = 5;

					*Result = *Utilities->ArrayAllocate(Size);
					return true;
				}

				CodaScriptCommandHandler(ArrayInsert)
				{
					ICodaScriptDataStore* Array = nullptr;
					ICodaScriptDataStore* Element = nullptr;
					CodaScriptNumericDataTypeT Index = -1;

					CodaScriptCommandExtractArgs(&Array, &Element, &Index);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					CodaScriptBackingStore* ElementStore = dynamic_cast<CodaScriptBackingStore*>(Element);
					SME_ASSERT(ArrayStore && ElementStore);

					Result->SetNumber(ArrayStore->GetArray()->Insert(ElementStore, Index));
					return true;
				}

				CodaScriptCommandHandler(ArrayErase)
				{
					ICodaScriptDataStore* Array = nullptr;
					CodaScriptNumericDataTypeT Index = -1;

					CodaScriptCommandExtractArgs(&Array, &Index);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					SME_ASSERT(ArrayStore);

					Result->SetNumber(ArrayStore->GetArray()->Erase(Index));
					return true;
				}

				CodaScriptCommandHandler(ArrayClear)
				{
					ICodaScriptDataStore* Array = nullptr;

					CodaScriptCommandExtractArgs(&Array);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					SME_ASSERT(ArrayStore);

					ArrayStore->GetArray()->Clear();
					return true;
				}

				CodaScriptCommandHandler(ArraySize)
				{
					ICodaScriptDataStore* Array = nullptr;

					CodaScriptCommandExtractArgs(&Array);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					SME_ASSERT(ArrayStore);

					Result->SetNumber(ArrayStore->GetArray()->Size());
					return true;
				}

				CodaScriptCommandHandler(ArrayInsertAt)
				{
					ICodaScriptDataStore* Array = nullptr;
					ICodaScriptDataStore* Element = nullptr;
					CodaScriptNumericDataTypeT Index = -1;

					CodaScriptCommandExtractArgs(&Array, &Element, &Index);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					CodaScriptBackingStore* ElementStore = dynamic_cast<CodaScriptBackingStore*>(Element);
					SME_ASSERT(ArrayStore && ElementStore);

					Result->SetNumber(ArrayStore->GetArray()->Insert(ElementStore, Index, false));
					return true;
				}

				CodaScriptCommandHandler(ArraySetAt)
				{
					ICodaScriptDataStore* Array = nullptr;
					ICodaScriptDataStore* Element = nullptr;
					CodaScriptNumericDataTypeT Index = -1;

					CodaScriptCommandExtractArgs(&Array, &Element, &Index);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					CodaScriptBackingStore* ElementStore = dynamic_cast<CodaScriptBackingStore*>(Element);
					SME_ASSERT(ArrayStore && ElementStore);

					Result->SetNumber(ArrayStore->GetArray()->Insert(ElementStore, Index, true));
					return true;
				}

				CodaScriptCommandHandler(ArrayAppend)
				{
					ICodaScriptDataStore* Array = nullptr;
					ICodaScriptDataStore* Element = nullptr;

					CodaScriptCommandExtractArgs(&Array, &Element);

					CodaScriptBackingStore* ArrayStore = dynamic_cast<CodaScriptBackingStore*>(Array);
					CodaScriptBackingStore* ElementStore = dynamic_cast<CodaScriptBackingStore*>(Element);
					SME_ASSERT(ArrayStore && ElementStore);

					Result->SetNumber(ArrayStore->GetArray()->Insert(ElementStore, -1, true));
					return true;
				}
			}
		}
	}
}