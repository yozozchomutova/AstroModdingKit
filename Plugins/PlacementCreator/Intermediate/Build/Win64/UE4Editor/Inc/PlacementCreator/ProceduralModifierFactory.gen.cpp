// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PlacementCreator/Public/ProceduralModifierFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralModifierFactory() {}
// Cross Module References
	PLACEMENTCREATOR_API UClass* Z_Construct_UClass_UProceduralModifierFactory_NoRegister();
	PLACEMENTCREATOR_API UClass* Z_Construct_UClass_UProceduralModifierFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_PlacementCreator();
// End Cross Module References
	void UProceduralModifierFactory::StaticRegisterNativesUProceduralModifierFactory()
	{
	}
	UClass* Z_Construct_UClass_UProceduralModifierFactory_NoRegister()
	{
		return UProceduralModifierFactory::StaticClass();
	}
	struct Z_Construct_UClass_UProceduralModifierFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UProceduralModifierFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_PlacementCreator,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UProceduralModifierFactory_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "ProceduralModifierFactory.h" },
		{ "ModuleRelativePath", "Public/ProceduralModifierFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UProceduralModifierFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProceduralModifierFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UProceduralModifierFactory_Statics::ClassParams = {
		&UProceduralModifierFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UProceduralModifierFactory_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UProceduralModifierFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UProceduralModifierFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UProceduralModifierFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UProceduralModifierFactory, 2071438161);
	template<> PLACEMENTCREATOR_API UClass* StaticClass<UProceduralModifierFactory>()
	{
		return UProceduralModifierFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UProceduralModifierFactory(Z_Construct_UClass_UProceduralModifierFactory, &UProceduralModifierFactory::StaticClass, TEXT("/Script/PlacementCreator"), TEXT("UProceduralModifierFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UProceduralModifierFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
