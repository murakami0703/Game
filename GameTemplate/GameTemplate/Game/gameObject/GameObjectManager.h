#pragma once
#include "IGameObject.h"


//�Q�[���I�u�W�F�N�g�̃v���C�I���e�B
enum {
	GameObjectPrio_MostHigh,	//�ŗD��B
	GameObjectPrio_High,		//�Q�Ԗڂ̗D��B
	GameObjectPrio_Middle,		//�R�Ԗڂ̗D��B
	GameObjectPrio_Low,			//�S�Ԗڂ̗D��B
	GameObjectPrio_MostLow,		//��ԒႢ�D��B
};


class GameObjectManager
{
public:

	void Init();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̒ǉ��B
	/// </summary>
	/// <param name="prio">�D�揇�ʁB�l���������قǗD�揇�ʂ͍����B</param>
	template <class T>
	T* NewGameObject( int prio = GameObjectPrio_Middle)
	{
		T* newObj = new T;
		newObj->SetPriority( prio );
		m_goList.push_back(newObj);
		//�D�揇�ʂ��g���ă��X�g���\�[�g����B
		m_goList.sort([&](IGameObject* lhs, IGameObject* rhs) {
			return lhs->GetPriority() < rhs->GetPriority();
		});
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����X�g����폜����B
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGameObject(IGameObject* go) {
		//���X�g���猟�����āB����������폜�B
		//���X�g���猟�����āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//�폜���N�G�X�g�𑗂�B
				go->RequestDelete();
				return;
			}
		}
	}
	/// <summary>
	/// �V���h�E�}�b�v���擾�B
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���擾�B
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}

	void SetMainSpriteMulColor(CVector4 mul) {
		m_copyMainRtToFrameBufferSprite.SetMulColor(mul);
	}
	/// <summary>
	/// �Q�[�����J�n����܂������H
	/// </summary>
	void SetGameFlag(bool flag) {
		m_gameStartFlag = flag;
	}
private:
	/// <summary>
	/// �v�������_�����O�B
	/// </summary>
	void PreRender();
	/// <summary>
	/// �t�H���[�h�����_�����O�B
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// �|�X�g�����_�����O�B
	/// </summary>
	void Post2DRender();

private:
	std::list< IGameObject* > m_goList;
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	ShadowMap m_shadowMap;					//�V���h�E�}�b�v�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	bool m_gameStartFlag = false;		//�Q�[���J�n�t���O�B
private:
	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�B
	ID3D11RenderTargetView* oldRenderTargetView;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* oldDepthStencilView;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	//�t���[���o�b�t�@�̃r���[�|�[�g
	D3D11_VIEWPORT oldViewports;
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	ID3D11DepthStencilState* depthStencilState;


};
extern GameObjectManager* g_goMgr;