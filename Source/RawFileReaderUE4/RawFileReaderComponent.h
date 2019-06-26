// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RawFileReaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAWFILEREADERUE4_API URawFileReaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URawFileReaderComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void ReadFile(FString filePath, int width, int height);

	UFUNCTION(BlueprintCallable)
	int32 GetMapValue(int x, int y);

	UPROPERTY(BlueprintReadOnly)
	bool IsMapReady = false;

	int16** Map = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
