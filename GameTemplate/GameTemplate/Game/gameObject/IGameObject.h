#pragma once

typedef unsigned char	GameObjectPrio;

class IGameObject
{
public:
	IGameObject() :
		m_priority(0)
	{
	}
	virtual ~IGameObject() {}
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
	/// 実行優先度を取得
	/// </summary>
	void SetPriority(GameObjectPrio  prio) 
	{
		m_priority = prio;
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

	bool IsStart() {
		return m_isStart;
	}

	void StartFlag(bool flag) {
		m_isStart = flag;
	}

private:
	bool m_isStart = false;			//Startの開始フラグ。
	bool isReqDelete = false;		//削除リクエスト。
	GameObjectPrio m_priority;		//実行優先度。
	

};

