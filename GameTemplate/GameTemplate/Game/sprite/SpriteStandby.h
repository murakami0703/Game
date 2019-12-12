#pragma once

extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h);
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer);
extern void InitSamplerState(ID3D11SamplerState*& samplerState);

struct SVertex {
	float position[4];		//���_���W�B4�v�f�Ȃ͍̂��͋C�ɂ��Ȃ��B
	float uv[2];			//UV���W�B���ꂪ�e�N�X�`�����W
};

