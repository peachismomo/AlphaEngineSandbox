#pragma once
#include "AEEngine.h"

namespace GameObjects {
	class GameObject {
	private:
		unsigned long		type;
		AEGfxVertexList*	pMesh;
		AEGfxTexture*		pTex;

	public:
		/*CONSTRUCTORS*/
		GameObject();
		GameObject(unsigned long objType, const s8* fileName);
		~GameObject();
		AEGfxTexture* GetTexture() const;
		AEGfxVertexList* GetMesh() const;
	};

	class GameObjInst {
	private:
		GameObject*		pObject;
		unsigned long	flag;
		AEVec2			scale;
		f32				w;
		f32				l;
		f32				h;
		AEVec2			pos;
		AEMtx33			transform;
		f32				elevation;

	public:
		/*CONSTRUCTORS*/
		GameObjInst();
		GameObjInst(GameObject* pGameObject, AEVec2 initScale,
			AEVec2 initPos = { 0, 0 }, f32 initElevation = 0);
		~GameObjInst();

		/*MEMBER FUNCTIONS*/
		AEVec2	ConvertIsometric();
		void	Render(AEVec2 offset = { 0, 0 }, AEVec2 spriteDimensions = { 0, 0 });
		void	Transform();
		AEVec2*	GetPosition();
		f32*	GetElevation();
	};

	class Character : public GameObjInst {
	private:
		f32				yVel;
		f32				yAccel;
		AEVec2			direction;
		bool			isMoving;
		bool			isJumping;
		AEVec2			spriteDimensions;
		AEVec2			spriteOffset;
		unsigned int	spriteIter;

	public:
		/*CONSTRUCTORS*/
		Character();
		Character(GameObject* pGameObject, AEVec2 initScale,
			AEVec2 initPos = { 0, 0 }, f32 initElevation = 0);
		~Character();

		/*MEMBER FUNCTIONS*/
		void	SetSprite(unsigned int width, unsigned int height);
		void	CheckInput();
		void	Jump();
		void	Move();
		void	Animate();
		AEVec2	GetSpriteOffset() const;
		AEVec2	GetSpriteDimensions() const;
		bool	CheckBoundary(AEVec2 position);
	};
}