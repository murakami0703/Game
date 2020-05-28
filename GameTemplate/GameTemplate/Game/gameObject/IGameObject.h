#pragma once

typedef unsigned char	GameObjectPrio;

class IGameObject
{
public:
	IGameObject() :
		m_priority(0),
		m_isStart(false)
	{
	}
	/// <summary>
	/// Updateの直前で呼ばれる開始処理
	/// </summary>
	/// <returns></returns>
	virtual bool Start() { return true; }

	/// <summary>
	/// 更新。
	/// </summary>

	virtual void Update() = 0;

	/// <summary>
	/// 描画。
	/// </summary>
	
	virtual void Render() {}

	virtual void PostRender(){}

	/// <summary>
	/// 実行優先度を取得
	/// </summary>
	GameObjectPrio GetPriority() const
	{
		return m_priority;
	}

	/// <summary>
	/// 削除リクエスト
	/// </summary>
	
	void RequestDelete() {
		isReqDelete = true;
	}
	/// <summary>
	/// 削除リクエストを受けているか調べる。
	/// </summary>
	/// <returns>
	/// trueが返ってきたら、リクエストを受けている。
	/// </returns>
	
	bool IsRequestDelete() {
		return isReqDelete;
	}
private:
	bool m_isStart;						//Startの開始フラグ。
	bool isReqDelete = false;		//削除リクエスト。
	GameObjectPrio m_priority;		//実行優先度。
	

};

