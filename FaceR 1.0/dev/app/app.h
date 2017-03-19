/*	
	**App��**
	ʵ��Ӧ��װ����࣬�ṩ��ʼ��Ӧ�õķ���������Window��View��ViewModel��Model����Ķ��󣬲������໥�󶨡�
	ʵ����Ϣѭ���ķ�����
	ʵ��Command����ִ�����п��Դ����µ�һ��Window��View��ViewModel��Model����Ķ��󣬲������໥�󶨡�
*/

#pragma once

#include"../common/common.h"
#include "../view model/viewmodel.h"
template <typename MainWindow, typename RegWindow, typename LoginWindow>
class FaceRApp
{
public:
	FaceRApp(MainWindow* Main, RegWindow* Reg, LoginWindow* Login) throw() : m_main(Main), m_reg(Reg), m_login(Login)
	{

	}
	void Initialize()
	{
		//load
		m_vmdl.set_face_checkRef(std::shared_ptr<face_check>(&m_fc_mdl));
		m_vmdl.set_predict_Ref(std::shared_ptr<predict>(&m_p_mdl));
		m_vmdl.set_trainRef(std::shared_ptr<train>(&m_t_mdl));
		//bind
		
		//notification
		m_vmdl.AddNotification(m_main->get_notification());
		m_vmdl.AddNotification(m_reg->get_notification());
		m_vmdl.AddNotification(m_login->get_notification());
		//command
		m_reg->SetSampleCommand(m_vmdl.get_PhoCommandRef());
		m_reg->SetRegEndCommand(m_vmdl.get_FinishCommandRef());
		m_login->SetLoginCommand(m_vmdl.get_LoginCommandRef());
	}
private:
	MainWindow *m_main;
	RegWindow *m_reg;
	LoginWindow *m_login;
	face_check m_fc_mdl;
	predict m_p_mdl;
	train m_t_mdl;
	FaceRViewModel m_vmdl;
};
