// Created by merisen in MerisenLLC

#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	actorTransformAndSpawn();
}

void AGeometryHubActor::onColorChanged(const FLinearColor& color, const FString& name)
{
}

void AGeometryHubActor::onTimerFinished(AActor* actor)
{

}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::actorTransformAndSpawn()
{
	UWorld* world = GetWorld();
	if (world)
	{
		for (int32 i = 0; i < 5; i++)
		{
			const FTransform gTransoform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f, 300.0f));
			ABaseGeometryActor* geometry = world->SpawnActor<ABaseGeometryActor>(geometryClass, gTransoform);
			if (geometry)
			{
				FGeometryData data;
				data.moveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				geometry->setGeometryData(data);
			}
		}

		for (int32 i = 0; i < 3; i++)
		{
			const FTransform gTransoform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f, 700.0f));
			ABaseGeometryActor* geometry = world->SpawnActorDeferred<ABaseGeometryActor>(geometryClass, gTransoform);
			if (geometry)
			{
				FGeometryData data;
				data.color = FLinearColor::MakeRandomColor();
				geometry->setGeometryData(data);
				geometry->FinishSpawning(gTransoform);
			}
		}

		for (const FGeometryPayload payload : gPayloads)
		{
			ABaseGeometryActor* geometry = world->SpawnActorDeferred<ABaseGeometryActor>(payload.geometryClass, payload.initTransform);
			if (geometry)
			{
				geometry->setGeometryData(payload.fgData);
				geometry->FinishSpawning(payload.initTransform);
			}
		}
	}
}

