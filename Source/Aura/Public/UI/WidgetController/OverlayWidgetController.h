// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVitalAttributeChangedSignature,float,NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);

struct FOnAttributeChangeData;


/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	/**
	 * @brief initialize widget value
	 */
	virtual void BroadcastInitialValues() override;

	/**
	 * @brief describe to attribute set
	 */
	virtual void BindCallbacksToDependencies() override;
	
	/** delegetas */
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnVitalAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnVitalAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnVitalAttributeChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnVitalAttributeChangedSignature OnMaxManaChanged;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRow;
	/** delegetas end*/
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	template<typename  T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
