//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fAgregarContribuyente.h"
#include "fOpciones.h"
#include "fModificarCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAgregarContribuyente *AgregarContribuyente;
//---------------------------------------------------------------------------
__fastcall TAgregarContribuyente::TAgregarContribuyente(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TAgregarContribuyente::VerificarDatos(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  if(Sender == EdCUIT)
	  {
		  if(Edit->Text != "__-________-_")
		  {
			 if(Edit->Text.Pos("_") == 0) //validacion de cuit
			 {
				int v1 = StrToInt(Edit->Text[1]) * 5;
				v1 = v1 + StrToInt(Edit->Text[2]) * 4;
				v1 = v1 + StrToInt(Edit->Text[4]) * 3;
				v1 = v1 + StrToInt(Edit->Text[5]) * 2;
				v1 = v1 + StrToInt(Edit->Text[6]) * 7;
				v1 = v1 + StrToInt(Edit->Text[7]) * 6;
				v1 = v1 + StrToInt(Edit->Text[8]) * 5;
				v1 = v1 + StrToInt(Edit->Text[9]) * 4;
				v1 = v1 + StrToInt(Edit->Text[10]) * 3;
				v1 = v1 + StrToInt(Edit->Text[11]) * 2;

				int v2 = v1 % 11;

				if(StrToInt(Edit->Text[13]) == (11 - v2))
				{
				   Edit->Color = clWindow;
				   Edit->ShowHint = false;
				   cuitOK = true;
				}
				else if(StrToInt(Edit->Text[13]) == 0 && (v2 == 0))
				{
				   Edit->Color = clWindow;
				   Edit->ShowHint = false;
				   cuitOK = true;
				}
				else
				{
				   Edit->Hint = "El cuit ingresado no es válido";
				   Edit->ShowHint = true;
				   Edit->Color = clWebLightCoral;
				   cuitOK = false;
				}
			 }
		  }
		  else
		  {
			 cuitOK = false;
			 Edit->Color = clWebLightCoral;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdCondIVA)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desCondicionFrenteIVA FROM condicionfrenteiva WHERE(idCondicionFrenteIVA = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desCondIVA->Caption = AuxQuery->FieldByName("desCondicionFrenteIVA")->AsString;
				Edit->Color = clWindow;
				civaOK = true;
			 }
			 else
			 {
				desCondIVA->Caption = "No existe el indicador de condicion";
				Edit->Color = clWebLightCoral;
				civaOK = false;
			 }
		  }
		  else
		  {
			 desCondIVA->Caption = "";
			 Edit->Color = clWebLightCoral;
			 civaOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdRazonSocial)
	  {
		  if(Edit->Text != "")
		  {
			 Edit->Color = clWindow;
			 razonOK = true;
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 razonOK = false;
		  }
	  }
	  else if(Sender == EdJurisdiccion)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desJurisdiccion FROM jurisdicciones WHERE(idJurisdiccion = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desJurisdiccion->Caption = AuxQuery->FieldByName("desJurisdiccion")->AsString;
				Edit->Color = clWindow;
				jurOK = true;
			 }
			 else
			 {
				desJurisdiccion->Caption = "No existe el indicador de jurisdiccion";
				Edit->Color = clWebLightCoral;
				jurOK = false;
			 }
		  }
		  else
		  {
			 desJurisdiccion->Caption = "";
			 Edit->Color = clWebLightCoral;
			 jurOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdCuenta)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 if(llamador == 2)
				AuxQuery->SQL->Add("SELECT desCuentaCompra FROM cuentascompras WHERE(idCuentaCompra = :v)");
			 else if(llamador == 3)
				AuxQuery->SQL->Add("SELECT desCuentaVenta FROM cuentasventas WHERE(idCuentaVenta = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				if(llamador == 2)
				   desCuenta->Caption = AuxQuery->FieldByName("desCuentaCompra")->AsString;
				if(llamador == 3)
				   desCuenta->Caption = AuxQuery->FieldByName("desCuentaVenta")->AsString;

				Edit->Color = clWindow;
				ctaOK = true;
			 }
			 else
			 {
				desCuenta->Caption = "No existe el indicador de cuenta";
				Edit->Color = clWebLightCoral;
				ctaOK = false;
			 }
		  }
		  else
		  {
			 desCuenta->Caption = "";
			 Edit->Color = clWebLightCoral;
			 ctaOK = false;
		  }
		  AuxQuery->Close();
	  }

   }
   else
	  ShowMessage("ERROR: El *Sender no es una clase TEdit");
}
//---------------------------------------------------------------------------

void TAgregarContribuyente::RestablecerFormulario(void)
{
   modificando = false;
   idModificado = 0;
   cuitOK = false;
   civaOK = false;
   jurOK = false;
   razonOK = false;
   AgregarContribuyente->Caption = "Agregar";
   BtnGuardar->Caption = "Guardar datos";

   EdRazonSocial->Text = "";
   EdCondIVA->Text = "";
   EdCuenta->Text = "";
   EdJurisdiccion->Text = "";
   CBCliente->ItemIndex = 0;

   desCondIVA->Caption = "-";
   desJurisdiccion->Caption = "-";
   desCuenta->Caption = "-";

   if(llamador == 1)
   {
      ctaOK = true;
      EdCUIT->Text = "__-________-_";
	  EdCuenta->Visible = false;
	  SpeedButton1->Visible = false;
	  Label7->Visible = false;
	  desCuenta->Visible = false;

	  Label5->Visible = true;
	  CBCliente->Visible = true;
	  EdCUIT->SetFocus();
   }
   else if(llamador == 2)
   {
	  ctaOK = false;
	  EdCuenta->Visible = true;
	  SpeedButton1->Visible = true;
	  Label7->Visible = true;
	  Label7->Caption = "Cuenta compra asociada";
	  desCuenta->Visible = true;

	  Label5->Visible = false;
	  CBCliente->Visible = false;
	  VerificarDatos(EdCUIT);
	  EdRazonSocial->SetFocus();
   }
   else if(llamador == 3)
   {
	  ctaOK = false;
	  EdCuenta->Visible = true;
	  SpeedButton1->Visible = true;
	  Label7->Visible = true;
	  Label7->Caption = "Cuenta venta asociada";
	  desCuenta->Visible = true;

	  Label5->Visible = false;
	  CBCliente->Visible = false;
	  VerificarDatos(EdCUIT);
	  EdRazonSocial->SetFocus();
   }

}
//---------------------------------------------------------------------------

int TAgregarContribuyente::YaExiste(AnsiString cuit)
{
   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add("SELECT idContribuyente FROM Contribuyentes WHERE(cuit = :v)");
   AuxQuery->ParamByName("v")->AsString = cuit;
   AuxQuery->Open();
   if(!AuxQuery->IsEmpty())
   {
	   int id = AuxQuery->FieldByName("idContribuyente")->AsInteger;
	   AuxQuery->Close();
	   return id;
   }
   else
   {
	   AuxQuery->Close();
	   return 0;
   }
}


//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::EdCUITKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdCUIT->Text = "___-________-_";
	  EdCUIT->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdCUIT->Text = "__-________-_";
	  EdCUIT->SelStart = 0;
   }
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::EdCUITKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 7;
	  Opciones->ShowModal();
	  Key = NULL;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = Opciones->idRetorno;
	  AuxQuery->Open();
	  EdCUIT->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  EdRazonSocial->SetFocus();
   }
   EdCUIT->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdCUITKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
   if(EdCUIT->SelStart == 2 || EdCUIT->SelStart == 11)
	  EdCUIT->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdCUITExit(TObject *Sender)
{
   VerificarDatos(Sender);

   int id = YaExiste(EdCUIT->Text);

   if(id > 0)
   {
	  if(llamador > 1)
	  {
		  Application->MessageBox(L"Este cuit ya existe. No se pueden realizar modificaciones desde esta pantalla",L"El cuit ya existe",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
          EdCUIT->Text = "__-________-_";
		  return;
      }

	  if(Application->MessageBox(L"Este cuit ya se encuentra registrado. Desea modificar datos del contribuyente?",L"Modificar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  {
		 EdCUIT->Text = "__-________-_";
		 EdCUIT->SetFocus();
		 return;
	  }

	  modificando = true;
	  idModificado = id;
	  cuitOLD = EdCUIT->Text;
	  AgregarContribuyente->Caption = "*Modificar datos*";
	  BtnGuardar->Caption = "Guardar cambios";

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT * FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = idModificado;
	  AuxQuery->Open();
	  if(!AuxQuery->IsEmpty())
	  {
		 EdRazonSocial->Text = AuxQuery->FieldByName("razonSocial")->AsString;
		 EdCondIVA->Text = AuxQuery->FieldByName("refCondicionFrenteIVA")->AsString;
		 EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsString;
		 CBCliente->ItemIndex = AuxQuery->FieldByName("esCliente")->AsInteger;
		 AuxQuery->Close();

		 EdRazonSocial->SetFocus();
		 EdCondIVA->SetFocus();
		 EdJurisdiccion->SetFocus();
		 CBCliente->SetFocus();
		 BtnGuardar->SetFocus();
		 cuitOK = true;
		 razonOK = true;
		 civaOK = true;
		 jurOK = true;
	  }
	  else
	  {
		 ShowMessage("Algo salio mal :(");
		 AuxQuery->Close();
	  }


   }
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::BtnCancelarClick(TObject *Sender)
{
   RestablecerFormulario();
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::EdCondIVAExit(TObject *Sender)
{
	VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdJurisdiccionExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::BtnGuardarClick(TObject *Sender)
{
   if(!(cuitOK && razonOK && civaOK && jurOK && ctaOK))
   {
	  Application->MessageBox(L"Hay errores en los datos ingresados.\nPor favor revise los casilleros resaltados",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 return;
   }
   if(Application->MessageBox(L"Se va a guardar la información ingresada, desea continuar?",L"Guardar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

   if(modificando)
	  if(Application->MessageBox(L"Se van a modificar los datos de un contribuyente previamente cargado\n\nREALMENTE DESEA CONTINUAR?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
		 return;


   Query1->Close();
   Query1->SQL->Clear();
   if(!modificando)
	  Query1->SQL->Add("INSERT INTO Contribuyentes VALUES(NULL, :v1, :v2, :v3, :v4, :v5)");
   else
   {
	  Query1->SQL->Add("UPDATE Contribuyentes SET razonSocial = :v1, cuit = :v2, refCondicionFrenteIVA = :v3, refJurisdiccion = :v4, esCliente = :v5 WHERE(idContribuyente = :id)");
	  Query1->ParamByName("id")->AsInteger = idModificado;
   }

   Query1->ParamByName("v1")->AsString = EdRazonSocial->Text;
   Query1->ParamByName("v2")->AsString = EdCUIT->Text;
   Query1->ParamByName("v3")->AsString = EdCondIVA->Text;
   Query1->ParamByName("v4")->AsString = EdJurisdiccion->Text;

   if(llamador == 1)
	  Query1->ParamByName("v5")->AsInteger = CBCliente->ItemIndex;
   else
	  Query1->ParamByName("v5")->AsInteger = 0;

   Query1->ExecSQL();


   if(!modificando && llamador != 1)
   {
	  int idNuevo = YaExiste(EdCUIT->Text);
	  if(idNuevo == 0)
	  {
		  ShowMessage("Error: No se encontro el contribuyente que acaba de agregarse :(");
		  return;
      }

	  Query1->Close();
	  Query1->SQL->Clear();

	  if(llamador == 2)
		 Query1->SQL->Add("INSERT INTO asociacionproveedores VALUES(NULL, :v1, :v2, :v3)");
	  else if(llamador == 3)
		 Query1->SQL->Add("INSERT INTO asociacionclientes VALUES(NULL, :v1, :v2, :v3)");

	  Query1->ParamByName("v1")->AsInteger = idContribuyente;
	  Query1->ParamByName("v2")->AsInteger = idNuevo;
	  Query1->ParamByName("v3")->AsString = EdCuenta->Text;
	  Query1->ExecSQL();
   }

   RestablecerFormulario();
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::EdRazonSocialExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAgregarContribuyente::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------


void __fastcall TAgregarContribuyente::EdCuentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdCondIVAKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
      Opciones->llamador = 6;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdCondIVA->Text = IntToStr(Opciones->idRetorno);
   }
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 5;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdJurisdiccion->Text = IntToStr(Opciones->idRetorno);
   }
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::EdCuentaKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  if(llamador == 2)
		 Opciones->llamador = 1;
	  else if(llamador == 3)
	     Opciones->llamador = 2;

	  Opciones->ShowModal();
	  Key = NULL;
	  EdCuenta->Text = IntToStr(Opciones->idRetorno);
   }
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::SpeedButton1Click(TObject *Sender)
{
   ModificarCuentas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TAgregarContribuyente::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE || Key == VK_RETURN)
	  AgregarContribuyente->Close();
}
//---------------------------------------------------------------------------

