extends Control

var text

func _ready():
	pass

func _process(delta):
	pass

#Muda o texto do label [[DEIXAR DE USAR DEPOIS]]!!
#var text = texto do label (string)
func _set_Text_Label(text):
	get_node("Label").set_text(text)

#Mudar a imagem do botão
#var button = nome do botão (string)
#var char   = letra do alfabeto (char)
#var path   = nome da pasta [certas ou erradas] (string)
func _set_Image_Button(button, char, path):
	var img = load('res://img/letras/'+path+'/letra-'+char+'.png')
	get_node(button).set_button_icon(img)

#faz alguma coisa que e ao mesmo tempo um monte de coisa...
#var letra = letra para o label
#var bnt   = botão que foi precionado
func _faz_alguma_coisa(letra, bnt):
	text = get_node("Label").get_text()+' '+letra
	get_node(bnt).set_disabled (true)
	_set_Image_Button(bnt, letra, 'certas')
	_set_Text_Label(text)

#Funções dos botões:
func _on_bntA_pressed():
	_faz_alguma_coisa('A', 'bntA')

func _on_bntB_pressed():
	_faz_alguma_coisa('B', 'bntB')

func _on_bntC_pressed():
	_faz_alguma_coisa('C', 'bntC')

func _on_bntD_pressed():
	_faz_alguma_coisa('D', 'bntD')

func _on_bntE_pressed():
	_faz_alguma_coisa('E', 'bntE')

func _on_bntF_pressed():
	_faz_alguma_coisa('F', 'bntF')

func _on_bntG_pressed():
	_faz_alguma_coisa('G', 'bntG')

func _on_bntH_pressed():
	_faz_alguma_coisa('H', 'bntH')

func _on_bntI_pressed():
	_faz_alguma_coisa('I', 'bntI')

func _on_bntJ_pressed():
	_faz_alguma_coisa('J', 'bntJ')

func _on_bntK_pressed():
	_faz_alguma_coisa('K', 'bntK')

func _on_bntL_pressed():
	_faz_alguma_coisa('L', 'bntL')

func _on_bntM_pressed():
	_faz_alguma_coisa('M', 'bntM')

func _on_bntN_pressed():
	_faz_alguma_coisa('N', 'bntN')

func _on_bntO_pressed():
	_faz_alguma_coisa('O', 'bntO')

func _on_bntP_pressed():
	_faz_alguma_coisa('P', 'bntP')

func _on_bntQ_pressed():
	_faz_alguma_coisa('Q', 'bntQ')

func _on_bntR_pressed():
	_faz_alguma_coisa('R', 'bntR')

func _on_bntS_pressed():
	_faz_alguma_coisa('S', 'bntS')

func _on_bntT_pressed():
	_faz_alguma_coisa('T', 'bntT')

func _on_bntU_pressed():
	_faz_alguma_coisa('U', 'bntU')

func _on_bntV_pressed():
	_faz_alguma_coisa('V', 'bntV')

func _on_bntW_pressed():
	_faz_alguma_coisa('W', 'bntW')

func _on_bntX_pressed():
	_faz_alguma_coisa('X', 'bntX')

func _on_bntY_pressed():
	_faz_alguma_coisa('Y', 'bntY')

func _on_bntZ_pressed():
	_faz_alguma_coisa('Z', 'bntZ')
