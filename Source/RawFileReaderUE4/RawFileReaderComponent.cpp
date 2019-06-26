// Fill out your copyright notice in the Description page of Project Settings.

#include "RawFileReaderComponent.h"
#include "Async.h"
#include <fstream>

// Sets default values for this component's properties
URawFileReaderComponent::URawFileReaderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URawFileReaderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URawFileReaderComponent::ReadFile(FString filePath, int width, int height) {
	TFunction<void()> Task = [=]() {
		UE_LOG(LogTemp, Warning, TEXT("Task called in C++"));

		std::ifstream floatFile(*filePath, std::ios::binary | std::ios::ate);

		Map = new int16_t*[width];

		if (floatFile.is_open()) {
			int fileSize = floatFile.tellg();
			floatFile.seekg(0);
			for (int i = 0; i < width; i++) {
				Map[i] = new int16_t[height];
				floatFile.read((char*)Map[i], height * sizeof(int16_t));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("File not found"));
		}
	};

	TFunction<void()> Callback = [this]() {
		UE_LOG(LogTemp, Warning, TEXT("Callback called in C++")); 
		IsMapReady = true;
	};

	Async(EAsyncExecution::ThreadPool, Task, Callback);
	
	UE_LOG(LogTemp, Warning, TEXT("Read file function ended in C++"));
}

int32 URawFileReaderComponent::GetMapValue(int x, int y) {
	return (int32)Map[x][y];
}

void URawFileReaderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

