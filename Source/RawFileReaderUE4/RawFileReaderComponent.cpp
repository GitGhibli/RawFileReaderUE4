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


// Called when the game starts
void URawFileReaderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URawFileReaderComponent::ReadFile(FString filePath, int Width, int Height) {
	//3625
	//6250
	TFunction<int16**()> Task = [filePath, Width, Height]()
		-> int16** {
		std::ifstream floatFile(*filePath, std::ios::binary | std::ios::ate);

		int16** map = new int16_t*[Width];

		if (floatFile.is_open()) {
			int fileSize = floatFile.tellg();
			floatFile.seekg(0);
			for (int i = 0; i < Width; i++) {
				map[i] = new int16_t[Height];
				floatFile.read((char*)map[i], Height * sizeof(int16_t));
			}
		}

		FPlatformProcess::Sleep(3);

		return map;
	};

	auto future = Async(EAsyncExecution::ThreadPool, Task);	

	Map = future.Get();
	
	UE_LOG(LogTemp, Warning, TEXT("File Uploaded in C++"));
}

int32 URawFileReaderComponent::GetMapValue(int x, int y) {
	return (int32)Map[x][y];
}

// Called every frame
void URawFileReaderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

