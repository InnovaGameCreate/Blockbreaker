#pragma once
class PhaseController
{
private:
	virtual void Draw() = 0;			//�`�揈��
	virtual void Update() = 0;			//�v�Z����
	virtual void Update_Final() {};		//Update��ɌĂ΂��
public:
	PhaseController() {};			//�R���X�g���N�^
	virtual ~PhaseController() {};	//�f�X�g���N�^

									//�������z�֐�(�K���I�[�o�[���C�h���邱�ƁI�I)
	virtual void Init_Draw() = 0;		//������(�`�揈��)
	virtual void Init_Update() = 0;		//������(�v�Z����)
	virtual void Finalize_Draw() = 0;	//�I������(�`�揈��)
	virtual void Finalize_Update() = 0;	//�I������(�v�Z����)

										//�`��ۂɌĂ΂��`��֐�
	virtual void DrawFunc() final {
		Draw();
	}

	//�`��ۂɌĂ΂��`��֐�
	virtual void UpdateFunc() final {
		Update_Final();
		Update();
	}

};

//�K��̃t�F�[�Y
class Phase_Default : public PhaseController
{
public:
	Phase_Default();
	~Phase_Default();
	void Init_Draw();
	void Init_Update();
	void Draw();
	void Update();
	void Finalize_Draw();
	void Finalize_Update();
};