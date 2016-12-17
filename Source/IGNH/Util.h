// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Util.generated.h"

/**
 * 
 */

 /*-------------------------------------------------
 -------------    Enum declaration    --------------
 -------------------------------------------------*/

UENUM(BlueprintType)
enum class EItemEnum : uint8
{
	IE_Wearable			UMETA(DisplayName = "Wearable"),
	IE_Useable			UMETA(DisplayName = "Useable")
};

/*-------------------------------------------------
-----------    Structure declaration    -----------
-------------------------------------------------*/



/*-------------------------------------------------
------------    Function declaration    -----------
-------------------------------------------------*/
UCLASS()
class IGNH_API UUtil : public UObject
{
	GENERATED_BODY()
	
	

	
	
	
};
