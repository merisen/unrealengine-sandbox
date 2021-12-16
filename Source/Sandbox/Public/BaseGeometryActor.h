// Created by merisen in MerisenLLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Movement")
	float amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType moveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float timerRate = 3.0f;
};

UCLASS()
class SANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	void setGeometryData(const FGeometryData& data) { gData = data; }

	UFUNCTION(BlueprintCallable)
	FGeometryData getGeometryData() const { return gData; }

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged onColorChanged;

	FOnTimerFinished onTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData gData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 weapNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int32 killNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float health = 4.3434f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool isDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool isWeap = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector initLocation;
	FTimerHandle timerHandle;

	const int32 maxTimerCount = 5;
	int32 timerCount = 0;

	void printTypes();
	void handleMovement();
	void setObjectColor(const FLinearColor& color);
	void onTimerFired();
};
