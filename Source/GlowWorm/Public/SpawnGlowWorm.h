// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnGlowWorm.generated.h"


USTRUCT()
struct FFlockMemberData {
	GENERATED_BODY()

	UPROPERTY()
		int32 InstanceIndex;
	UPROPERTY()
		FVector Velocity;
	UPROPERTY()
		FVector WanderPosition;
	UPROPERTY()
		FTransform Transform;
	UPROPERTY()
		float ElapsedTimeSinceLastWander;
	UPROPERTY()
		bool bIsFlockLeader;

	FFlockMemberData() {
		InstanceIndex = 0;
		Velocity = FVector(0, 0, 0);
		ElapsedTimeSinceLastWander = 0.0f;
		WanderPosition = FVector(0, 0, 0);
		bIsFlockLeader = false;
	};
};


UCLASS()
class GLOWWORM_API ASpawnGlowWorm : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpawnGlowWorm();
	UPROPERTY(BlueprintReadWrite, Category = Flock)
		int NumFlockInstance;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Flock)
		class USphereComponent* pSphereComponent;
	UPROPERTY(BlueprintReadOnly, Category = Flock)
		int32 NumFlock;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockRadius = 1000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMinSpeed = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMaxSpeed = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockWanderUpdateRate = 2000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMinWanderDistance = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMateAwarnessRadius = 400.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockEnemyAwarnessRadius = 400.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FollowScale = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float AlignScale = 0.4f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float CohesionScale = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float SeperationScale = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FleeScale = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float SeperationRadius = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMaxSteeringForce = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		float FlockMateRotationRate = 0.3f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringRadius = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringAlign = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringFollow = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringSeparate = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringCohesion = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringFlee = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawSteeringFleeThreat = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool DrawLeaderTarget = false;
	TArray<FFlockMemberData> mFlockMemberData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		TArray<AActor*> Threats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		bool ChangeLeaderLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		TSubclassOf<class AGrowWormInstance> GrowWormInstance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Flock)
		TArray<AActor*> GrowWormInstanceArr;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Flock)
		void AddGlowWormToWorldSpace(const FTransform& WorldTransform);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		FVector GetRandomWanderLocation();

	TArray<int32> GetNearbyFlockMates(int32 flockmember);
	FVector SteeringWander(FFlockMemberData& flocker);
	FVector SteeringAlign(FFlockMemberData& flocker, TArray<int32>& flockMates);
	FVector SteeringSeperate(FFlockMemberData& flocker, TArray<int32>& flockMates);
	FVector SteeringCohesion(FFlockMemberData& flocker, TArray<int32>& flockMates);
	FVector SteeringFollow(FFlockMemberData& flocker, int32 flockleader);
	FVector SteeringFlee(FFlockMemberData& flocker);
	FRotator FindLookAtRotation(FVector start, FVector end);

};