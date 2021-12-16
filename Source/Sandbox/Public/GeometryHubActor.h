// Created by merisen in MerisenLLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> geometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData fgData;

	UPROPERTY(EditAnywhere)
	FTransform initTransform;
};

UCLASS()
class SANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> geometryClass;

	UPROPERTY(EditAnywhere)
	UClass* myClass;

	UPROPERTY(EditAnywhere)
	ABaseGeometryActor* geometryObject;

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> gPayloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void actorTransformAndSpawn();

private:
	void onColorChanged(const FLinearColor& color, const FString& name);
	void onTimerFinished(AActor* actor);
};
