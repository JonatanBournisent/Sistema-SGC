//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#include <Windows.h>
#pragma hdrstop

#include "fCargarVentas.h"
#include "fOpciones.h"
#include "fAgregarContribuyente.h"
#include "uMostrarComprobantes.h"
#include "fModificarCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCargarVentas *CargarVentas;
//---------------------------------------------------------------------------
__fastcall TCargarVentas::TCargarVentas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//***************************************************************************
//***************INICIO DE DEFINICION DE FUNCIONES***************************
//***************************************************************************

//---------------------------------------------------------------------------

void TCargarVentas::LimpiarEdit(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  Edit->Text = Edit->Text.SubString(3,Edit->Text.Length()-2);
	  Edit->SelectAll();
   }
}
//---------------------------------------------------------------------------

void TCargarVentas::DarFormatoEdit(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  if(Edit->Text == "")
		 Edit->Text = "0";
	  else if(Edit->Text.Pos("-"))
	     Edit->Text = Edit->Text.Delete(Edit->Text.Pos("-"),1);
	  Edit->Text = FormatFloat("$ 0.#0", StrToFloat(Edit->Text));
   }
}
//---------------------------------------------------------------------------

void TCargarVentas::CalcularIVA(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  if(Sender == EdNetoGravado1 && al1OK)
	  {
		 IVA1 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali1 / 100.0;
		 LabIVA1->Caption = FormatFloat("$ 0.#0", IVA1);
	  }

	  else if(Sender == EdNetoGravado2 && al2OK)
	  {
		 IVA2 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali2 / 100.0;
		 LabIVA2->Caption = FormatFloat("$ 0.#0", IVA2);
	  }

	  else if(Sender == EdNetoGravado3 && al3OK)
	  {
		 IVA3 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali3 / 100.0;
		 LabIVA3->Caption = FormatFloat("$ 0.#0", IVA3);
	  }

	  else if(Sender == EdNetoGravado4 && al4OK)
	  {
		 IVA4 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali4 / 100.0;
		 LabIVA4->Caption = FormatFloat("$ 0.#0", IVA4);
	  }

	  if(!al1OK)
		 LabIVA1->Caption = "-";

	  if(!al2OK)
		 LabIVA2->Caption = "-";

	  if(!al3OK)
		 LabIVA3->Caption = "-";

	  if(!al4OK)
		 LabIVA4->Caption = "-";
   }
}
//---------------------------------------------------------------------------

void TCargarVentas::DarFormatoEntrada(System::WideChar &Key)
{
   if(Key == '.')
	  Key = FormatSettings.DecimalSeparator;
   else if((Key > '9' || Key < '0') && Key != '\b')
	  Key = NULL;
}
//---------------------------------------------------------------------------

void TCargarVentas::SeleccionarTodo(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  Edit->SelectAll();
   }
}
//---------------------------------------------------------------------------

void TCargarVentas::VerificarDatos(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  if(Sender == EdContribuyente)
	  {
		  if(Edit->Text != "__-________-_")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();

			 if(RG1->ItemIndex == 0) //si es un Z, la jurisdiccion se asocia al contribuyente, en otro caso al cliente
				AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");
			 else if(RG1->ItemIndex == 1)
				AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refJurisdiccion, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");

			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desContribuyente->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idContribuyente = AuxQuery->FieldByName("idContribuyente")->AsInteger;
				Edit1->Text = IntToStr(idContribuyente);
				civaCont = AuxQuery->FieldByName("refCondicionFrenteIVA")->AsInteger;
				if(RG1->ItemIndex == 1)
				   EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsInteger;
				Edit->Color = clWindow;
				contOK = true;
			 }
			 else
			 {
				desContribuyente->Caption = "Contribuyente desconocido";
				idContribuyente = 0;
				Edit1->Text = "";
				if(RG1->ItemIndex == 1)
				   EdJurisdiccion->Text = "";
				Edit->Color = clWebLightCoral;
				contOK = false;
			 }
		  }
		  else
		  {
			 desContribuyente->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idContribuyente = 0;
			 Edit1->Text = "";
			 if(RG1->ItemIndex == 1)
				   EdJurisdiccion->Text = "";
			 contOK = false;
		  }
		  AuxQuery->Close();

		  if(RG1->ItemIndex == 1)
			 VerificarDatos(EdJurisdiccion);

		  if(cliOK && contOK)
		  {
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT refCuentaVenta FROM asociacionclientes WHERE(refContribuyente = :v1 AND refCliente = :v2)");
			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
             AuxQuery->ParamByName("v2")->AsString = idCliente;
			 AuxQuery->Open();
			 EdCuentaVenta->Text = AuxQuery->FieldByName("refCuentaVenta")->AsString;
			 AuxQuery->Close();

			 VerificarDatos(EdCuentaVenta);
          }
	  }
	  else if(Sender == EdCliente)
	  {
		  if(Edit->Text != "__-________-_" && idCliente != idContribuyente)
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 if(RG1->ItemIndex == 0)
				AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refJurisdiccion, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");
			 if(RG1->ItemIndex == 1)
				AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");

			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desCliente->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idCliente = AuxQuery->FieldByName("idContribuyente")->AsInteger;
                Edit2->Text = IntToStr(idCliente);
				civaCli = AuxQuery->FieldByName("refCondicionFrenteIVA")->AsInteger;
				if(RG1->ItemIndex == 0)
				   EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsInteger;

				Edit->Color = clWindow;
				cliOK = true;
			 }
			 else
			 {
				desCliente->Caption = "Cliente desconocido";
				idCliente = 0;
				Edit2->Text = "";
				if(RG1->ItemIndex == 0)
				   EdJurisdiccion->Text = "";
				Edit->Color = clWebLightCoral;
				cliOK = false;
			 }

			 if(!cliOK && Edit->Text.Pos("_") == 0)
				AgCliente->Enabled = true;
			 else
				AgCliente->Enabled = false;
		  }
		  else
		  {
			 desCliente->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idCliente = 0;
             Edit2->Text = "";
			 if(RG1->ItemIndex == 0)
				EdJurisdiccion->Text = "";

			 cliOK = false;
			 AgCliente->Enabled = false;
		  }
		  AuxQuery->Close();

		  if(RG1->ItemIndex == 0)
			 VerificarDatos(EdJurisdiccion);

		  if(cliOK && contOK)
		  {
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT refCuentaVenta FROM asociacionclientes WHERE(refContribuyente = :v1 AND refCliente = :v2)");
			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
             AuxQuery->ParamByName("v2")->AsString = idCliente;
			 AuxQuery->Open();
			 EdCuentaVenta->Text = AuxQuery->FieldByName("refCuentaVenta")->AsString;
			 AuxQuery->Close();

			 VerificarDatos(EdCuentaVenta);
          }
	  }
	  else if(Sender == EdPeriodo)
	  {
		  if(Edit->Text != "__/____")
		  {
			 if(Edit->Text.Pos("_") > 0)
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "No se completó el período";
				 Edit->ShowHint = true;
				 perOK = false;
			 }
			 else if(!IsValidDate(StrToInt(Edit->Text.SubString(4,4)), StrToInt(Edit->Text.SubString(1,2)), 1))
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "El período ingresado no representa una fecha válida";
				 Edit->ShowHint = true;
				 perOK = false;
			 }
			 else if(fechOK && ((StrToInt(EdFecha->Text.SubString(7,4)) > StrToInt(Edit->Text.SubString(4,4))) ||
					((StrToInt(EdFecha->Text.SubString(7,4)) <= StrToInt(Edit->Text.SubString(4,4))) &&
					(StrToInt(EdFecha->Text.SubString(4,2)) > StrToInt(Edit->Text.SubString(1,2))))))
			 {

				Edit->Color = clWebLightCoral;
				Edit->Hint = "El período ingresado es inferior a la fecha";
				Edit->ShowHint = true;
				fechOK = false;
			 }
			 else
			 {
				 Edit->Color = clWindow;
				 Edit->ShowHint = false;
				 perOK = true;
			 }
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se completó el período";
			 Edit->ShowHint = true;
			 perOK = false;
		  }
	  }
	  else if(Sender == EdFecha)
	  {
		  if(Edit->Text != "__/__/____")
		  {
			 if(Edit->Text.Pos("_") > 0)
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "No se completó la fecha";
				 Edit->ShowHint =
				  true;
				 fechOK = false;
			 }
			 else if(!IsValidDate(StrToInt(Edit->Text.SubString(7,4)), StrToInt(Edit->Text.SubString(4,2)), StrToInt(Edit->Text.SubString(1,2))))
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "La fecha ingresada no es válida";
				 Edit->ShowHint = true;
				 fechOK = false;
			 }
			 else if(perOK && ((StrToInt(Edit->Text.SubString(7,4)) > StrToInt(EdPeriodo->Text.SubString(4,4))) ||
					((StrToInt(Edit->Text.SubString(7,4)) <= StrToInt(EdPeriodo->Text.SubString(4,4))) &&
					(StrToInt(Edit->Text.SubString(4,2)) > StrToInt(EdPeriodo->Text.SubString(1,2))))))
			 {

				Edit->Color = clWebLightCoral;
				Edit->Hint = "La fecha ingresada es posterior al período";
				Edit->ShowHint = true;
				fechOK = false;
			 }
			 else
			 {
				 Edit->Color = clWindow;
				 Edit->ShowHint = false;
				 fechOK = true;
			 }

		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se completó la fecha";
			 Edit->ShowHint = true;
			 fechOK = false;
		  }
	  }
	  else if(Sender == EdCuentaVenta)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desCuentaVenta FROM cuentasventas WHERE(idCuentaVenta = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desCuentaVenta->Caption = AuxQuery->FieldByName("desCuentaVenta")->AsString;
				Edit->Color = clWindow;
				ccOK = true;
			 }
			 else
			 {
				desCuentaVenta->Caption = "No existe el indicador de cuenta";
				Edit->Color = clWebLightCoral;
				ccOK = false;
			 }
		  }
		  else
		  {
			 desCuentaVenta->Caption = "";
			 Edit->Color = clWebLightCoral;
			 ccOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdDocumento)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desDocumento FROM documentos WHERE(idDocumento = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desDocumento->Caption = AuxQuery->FieldByName("desDocumento")->AsString;
				Edit->Color = clWindow;
				docOK = true;
			 }
			 else
			 {
				desDocumento->Caption = "No existe el indicador de documento";
				Edit->Color = clWebLightCoral;
				docOK = false;
			 }
		  }
		  else
		  {
			 desDocumento->Caption = "";
			 Edit->Color = clWebLightCoral;
			 docOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdTipo)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desTipo FROM tipos WHERE(idTipo = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desTipo->Caption = AuxQuery->FieldByName("desTipo")->AsString;
				Edit->Color = clWindow;
				tipoOK = true;
			 }
			 else
			 {
				desTipo->Caption = "No existe el indicador de tipo";
				Edit->Color = clWebLightCoral;
				tipoOK = false;
			 }
		  }
		  else
		  {
			 desTipo->Caption = "";
			 Edit->Color = clWebLightCoral;
			 tipoOK = false;
		  }
		  AuxQuery->Close();
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
				juriOK = true;
			 }
			 else
			 {
				desJurisdiccion->Caption = "No existe el indicador de jurisdiccion";
				Edit->Color = clWebLightCoral;
				juriOK = false;
			 }
		  }
		  else
		  {
			 desJurisdiccion->Caption = "";
			 Edit->Color = clWebLightCoral;
			 juriOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdAlicuota1 || Sender == EdAlicuota2 || Sender == EdAlicuota3 || Sender == EdAlicuota4)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT valor FROM alicuotas WHERE(idAlicuota = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				if(Sender == EdAlicuota1)
				{
				   desAlicuota1->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali1 = AuxQuery->FieldByName("valor")->AsFloat;
				   al1OK = true;
				}

				else if(Sender == EdAlicuota2)
				{
				   desAlicuota2->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali2 = AuxQuery->FieldByName("valor")->AsFloat;
				   al2OK = true;
				}

				else if(Sender == EdAlicuota3)
				{
				   desAlicuota3->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali3 = AuxQuery->FieldByName("valor")->AsFloat;
				   al3OK = true;
				}

				else if(Sender == EdAlicuota4)
				{
				   desAlicuota4->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali4 = AuxQuery->FieldByName("valor")->AsFloat;
				   al4OK = true;
				}

				Edit->Color = clWindow;

			 }
			 else
			 {
				if(Sender == EdAlicuota1)
				{
				   desAlicuota1->Caption = "X";
				   ali1 = 0.0;
				   al1OK = false;
				}
				else if(Sender == EdAlicuota2)
				{
				   desAlicuota2->Caption = "X";
				   ali2 = 0.0;
				   al2OK = false;
				}
				else if(Sender == EdAlicuota3)
				{
				   desAlicuota3->Caption = "X";
				   ali3 = 0.0;
				   al3OK = false;
				}
				else if(Sender == EdAlicuota4)
				{
				   desAlicuota4->Caption = "X";
				   ali4 = 0.0;
				   al4OK = false;
				}

				Edit->Color = clWebLightCoral;
			 }
		  }
		  else
		  {
			 if(Sender == EdAlicuota1)
			 {
				desAlicuota1->Caption = "";
				ali1 = 0.0;
				al1OK = false;
			 }
			 else if(Sender == EdAlicuota2)
			 {
				desAlicuota2->Caption = "";
				ali2 = 0.0;
				al2OK = false;
			 }
			 else if(Sender == EdAlicuota3)
			 {
				desAlicuota3->Caption = "";
				ali3 = 0.0;
				al3OK = false;
			 }
			 else if(Sender == EdAlicuota4)
			 {
				desAlicuota4->Caption = "";
				ali4 = 0.0;
				al4OK = false;
			 }

			 Edit->Color = clWebLightCoral;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdPtoVenta)
	  {
		  switch(Edit->Text.Length())
		  {
			 case 0: Edit->Text = "00000"; break;
			 case 1: Edit->Text = Edit->Text.Insert("0000", 1); break;
			 case 2: Edit->Text = Edit->Text.Insert("000", 1); break;
			 case 3: Edit->Text = Edit->Text.Insert("00", 1); break;
			 case 4: Edit->Text = Edit->Text.Insert("0", 1); break;
		  }

		  if(Edit->Text != "00000")
		  {
			 Edit->Color = clWindow;
			 Edit->ShowHint = false;
			 ptoOK = true;
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se indica el punto de venta";
			 Edit->ShowHint = true;
			 ptoOK = false;
		  }
	  }
	  else if(Sender == EdNroComprobante)
	  {
		  switch(Edit->Text.Length())
		  {
			 case 0: Edit->Text = "00000000"; break;
			 case 1: Edit->Text = Edit->Text.Insert("0000000", 1); break;
			 case 2: Edit->Text = Edit->Text.Insert("000000", 1); break;
			 case 3: Edit->Text = Edit->Text.Insert("00000", 1); break;
			 case 4: Edit->Text = Edit->Text.Insert("0000", 1); break;
			 case 5: Edit->Text = Edit->Text.Insert("000", 1); break;
			 case 6: Edit->Text = Edit->Text.Insert("00", 1); break;
			 case 7: Edit->Text = Edit->Text.Insert("0", 1); break;
		  }

		  if(Edit->Text != "00000000")
		  {
			 Edit->Color = clWindow;
			 Edit->ShowHint = false;
			 nroOK = true;
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se indica el número de comprobante";
			 Edit->ShowHint = true;
			 nroOK = false;
		  }
	  }
   }
   else
	  ShowMessage("ERROR: El *Sender no es una clase TEdit");
}
//---------------------------------------------------------------------------

void TCargarVentas::ActualizarTotal(void)
{
   float total = StrToFloat(EdNetoGravado1->Text.SubString(3,EdNetoGravado1->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado2->Text.SubString(3,EdNetoGravado2->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado3->Text.SubString(3,EdNetoGravado3->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado4->Text.SubString(3,EdNetoGravado4->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesIVA->Text.SubString(3,EdRetencionesIVA->Text.Length()-2));
   total = total + StrToFloat(EdPercepcionesIVA->Text.SubString(3,EdPercepcionesIVA->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesIB->Text.SubString(3,EdRetencionesIB->Text.Length()-2));
   total = total + StrToFloat(EdPercepcionesIB->Text.SubString(3,EdPercepcionesIB->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesGanancias->Text.SubString(3,EdRetencionesGanancias->Text.Length()-2));
   total = total + StrToFloat(EdConcNoGravados->Text.SubString(3,EdConcNoGravados->Text.Length()-2));
   total = total + StrToFloat(EdExentos->Text.SubString(3,EdExentos->Text.Length()-2));

   total = total + IVA1 + IVA2 + IVA3 + IVA4;

   EdTotal->Text = FormatFloat("$ 0.#0", total);
}
//---------------------------------------------------------------------------

int TCargarVentas::YaExiste(void) //Si ya existe el comprobante retorna el idComprobanteVenta, si no, retorna 0
{
   // Ya existe el mismo comprobante?

   if(EdContribuyente->Text == "__-________-_" || EdPtoVenta->Text == "00000" || EdNroComprobante->Text == "00000000")
	  return 0;
   if(EdDocumento->Text == "" || EdTipo->Text == "")
	  return 0;

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add("SELECT idContribuyente FROM contribuyentes WHERE(cuit = :v)");
   AuxQuery->ParamByName("v")->AsString = EdContribuyente->Text;
   AuxQuery->Open();
   if(!AuxQuery->IsEmpty())
   {
	  int refContribuyente = AuxQuery->FieldByName("idContribuyente")->AsInteger;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idComprobanteVenta FROM comprobantesventas WHERE(refContribuyente = :v1 AND ptoVenta = :v2 AND nroComprobante = :v3 AND refDocumento = :v4 AND refTipo = :v5)");
	  AuxQuery->ParamByName("v1")->AsInteger = refContribuyente;
	  AuxQuery->ParamByName("v2")->AsString = EdPtoVenta->Text;
	  AuxQuery->ParamByName("v3")->AsString = EdNroComprobante->Text;
	  AuxQuery->ParamByName("v4")->AsString = EdDocumento->Text;
	  AuxQuery->ParamByName("v5")->AsString = EdTipo->Text;
	  AuxQuery->Open();
	  if(AuxQuery->IsEmpty())
	  {
		 AuxQuery->Close();
		 return 0;
	  }
	  int id = AuxQuery->FieldByName("idComprobanteVenta")->AsInteger;
	  AuxQuery->Close();
	  return id;
   }
   AuxQuery->Close();
   return 0;
}
//---------------------------------------------------------------------------

void TCargarVentas::TraerDatos(int idCompVenta)
{
    AuxQuery->Close();
	AuxQuery->SQL->Clear();
	AuxQuery->SQL->Add("SELECT * FROM comprobantesventas WHERE(idComprobanteVenta = :v)");
	AuxQuery->ParamByName("v")->AsInteger = idCompVenta;
	AuxQuery->Open();

	EdAlicuota1->Text = AuxQuery->FieldByName("refAlicuota1")->AsString;
	EdAlicuota2->Text = AuxQuery->FieldByName("refAlicuota2")->AsString;
	EdAlicuota3->Text = AuxQuery->FieldByName("refAlicuota3")->AsString;
	EdAlicuota4->Text = AuxQuery->FieldByName("refAlicuota4")->AsString;

	EdPeriodo->Text = FormatDateTime("mm/yyyy", AuxQuery->FieldByName("fechaPeriodo")->AsDateTime);
	EdFecha->Text = FormatDateTime("dd/mm/yyyy", AuxQuery->FieldByName("fechaComprobante")->AsDateTime);

	if(AuxQuery->FieldByName("anulado")->AsInteger == 1)
	   ChAnulado->Checked = true;
	else
	   ChAnulado->Checked = false;

	EdCuentaVenta->Text = AuxQuery->FieldByName("refCuentaVenta")->AsString;
	EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsString;

	EdNetoGravado1->Text = AuxQuery->FieldByName("netoGravado1")->AsString;
	DarFormatoEdit(EdNetoGravado1);
	EdNetoGravado2->Text = AuxQuery->FieldByName("netoGravado2")->AsString;
	DarFormatoEdit(EdNetoGravado2);
	EdNetoGravado3->Text = AuxQuery->FieldByName("netoGravado3")->AsString;
	DarFormatoEdit(EdNetoGravado3);
	EdNetoGravado4->Text = AuxQuery->FieldByName("netoGravado4")->AsString;
	DarFormatoEdit(EdNetoGravado4);
	EdRetencionesIVA->Text = AuxQuery->FieldByName("retencionesIVA")->AsString;
	DarFormatoEdit(EdRetencionesIVA);
	EdPercepcionesIVA->Text = AuxQuery->FieldByName("percepcionesIVA")->AsString;
	DarFormatoEdit(EdPercepcionesIVA);
	EdRetencionesIB->Text = AuxQuery->FieldByName("retencionesIB")->AsString;
	DarFormatoEdit(EdRetencionesIB);
	EdPercepcionesIB->Text = AuxQuery->FieldByName("percepcionesIB")->AsString;
	DarFormatoEdit(EdPercepcionesIB);
	EdRetencionesGanancias->Text = AuxQuery->FieldByName("retencionesGanancias")->AsString;
	DarFormatoEdit(EdRetencionesGanancias);
	EdConcNoGravados->Text = AuxQuery->FieldByName("conceptosNoGravados")->AsString;
	DarFormatoEdit(EdConcNoGravados);
	EdExentos->Text = AuxQuery->FieldByName("exentos")->AsString;
	DarFormatoEdit(EdExentos);
	EdTotal->Text = AuxQuery->FieldByName("total")->AsString;
	DarFormatoEdit(EdTotal);

	AuxQuery->Close();

	VerificarDatos(EdCuentaVenta);
	VerificarDatos(EdAlicuota1);
	VerificarDatos(EdAlicuota2);
	VerificarDatos(EdAlicuota3);
	VerificarDatos(EdAlicuota4);

	VerificarDatos(EdPeriodo);
	VerificarDatos(EdFecha);
	VerificarDatos(EdJurisdiccion);

	CalcularIVA(EdNetoGravado1);
	CalcularIVA(EdNetoGravado2);
	CalcularIVA(EdNetoGravado3);
	CalcularIVA(EdNetoGravado4);
}
//---------------------------------------------------------------------------

void TCargarVentas::RestablecerFormulario(void)
{
	EdContribuyente->Text = "__-________-_";
	EdContribuyente->Color = clWindow;
	EdCliente->Text = "__-________-_";
	EdCliente->Color = clWindow;
	EdPeriodo->Text = "__/____";
	EdPeriodo->Color = clWindow;
	EdFecha->Text = "__/__/____";
	EdFecha->Color = clWindow;
	EdPtoVenta->Text = "00000";
	EdPtoVenta->Color = clWindow;
	EdNroComprobante->Text = "00000000";
	EdNroComprobante->Color = clWindow;
	EdTipo->Text = "";
	EdTipo->Color = clWindow;
	EdDocumento->Text = "";
	EdDocumento->Color = clWindow;
	EdJurisdiccion->Text = "";
    EdJurisdiccion->Color = clWindow;
	EdAlicuota1->Text = 1;
	EdAlicuota2->Text = 2;
	EdAlicuota3->Text = 3;
	EdAlicuota4->Text = 4;
	EdCuentaVenta->Text = "";
	EdCuentaVenta->Color = clWindow;
	EdNetoGravado1->Text = "$ 0,00";
	EdNetoGravado2->Text = "$ 0,00";
	EdNetoGravado3->Text = "$ 0,00";
	EdNetoGravado4->Text = "$ 0,00";
	EdRetencionesIVA->Text = "$ 0,00";
	EdPercepcionesIVA->Text = "$ 0,00";
	EdRetencionesIB->Text = "$ 0,00";
	EdPercepcionesIB->Text = "$ 0,00";
	EdRetencionesGanancias->Text = "$ 0,00";
	EdConcNoGravados->Text = "$ 0,00";
	EdExentos->Text = "$ 0,00";
	EdTotal->Text = "$ 0,00";

	Edit1->Text = "";
	Edit2->Text = "";

	desContribuyente->Caption = "-";
	desCliente->Caption = "-";
	desCuentaVenta->Caption = "-";
	desDocumento->Caption = "-";
	desTipo->Caption = "-";
	desAlicuota1->Caption = "21%";
	desAlicuota2->Caption = "10,5%";
	desAlicuota3->Caption = "27%";
	desAlicuota4->Caption = "0,0%";

	modificando = false;
	idModificado = 0;
	idContribuyente = 0;
	idCliente = 0;
	CargarVentas->Caption = "Cargar comprobantes de ventas";
	BtnAgregarComp->Caption = "Guardar";
	BtnAgregarYCont->Caption = "Guardar y cargar otro";
	btEliminarComp->Enabled = false;

	contOK = false;
	perOK = false;
	fechOK = false;
	cliOK = false;
	ptoOK = false;
	nroOK = false;
	ccOK = false;
	tipoOK = false;
	docOK = false;
	juriOK = false;
	al1OK = true;
	al2OK = true;
	al3OK = true;
	al4OK = true;
	AgCliente->Enabled = false;

	IVA1 = 0.0;
	IVA2 = 0.0;
	IVA3 = 0.0;
	IVA4 = 0.0;

	ali1 = 21.0;
	ali2 = 10.5;
	ali3 = 27.0;
	ali4 = 0.0;

	LabIVA1->Caption = "$ 0,00";
	LabIVA2->Caption = "$ 0,00";
	LabIVA3->Caption = "$ 0,00";
	LabIVA4->Caption = "$ 0,00";

	ChAnulado->Checked = false;


   if(RG1->ItemIndex == 0)
   {

	   EdCliente->Enabled = true;
	   EdDocumento->Enabled = true;
	   EdTipo->Enabled = true;
	   EdRetencionesIVA->Enabled = true;
	   EdPercepcionesIVA->Enabled = true;
	   EdRetencionesIB->Enabled = true;
	   EdPercepcionesIB->Enabled = true;
	   EdRetencionesGanancias->Enabled = true;
   }
   else if(RG1->ItemIndex == 1)
   {

	   EdCliente->Text = "00-00000000-0";
	   VerificarDatos(EdCliente);
	   EdCliente->Enabled = false;

	   EdDocumento->Text = "2";
	   VerificarDatos(EdDocumento);
	   EdDocumento->Enabled = false;

	   EdTipo->Text = "6";
	   VerificarDatos(EdTipo);
	   EdTipo->Enabled = false;

	   EdRetencionesIVA->Enabled = false;
	   EdPercepcionesIVA->Enabled = false;
	   EdRetencionesIB->Enabled = false;
	   EdPercepcionesIB->Enabled = false;
	   EdRetencionesGanancias->Enabled = false;
   }


	EdContribuyente->SetFocus();
}
//---------------------------------------------------------------------------

void TCargarVentas::RestablecerFormularioCont(void)
{
	AnsiString s1 = EdContribuyente->Text;
	AnsiString s2 = EdPeriodo->Text;
	AnsiString s3 = EdCliente->Text;
	AnsiString s4 = EdPtoVenta->Text;
	AnsiString s5 = EdNroComprobante->Text;

	RestablecerFormulario();

	EdContribuyente->Text = s1;
	EdPeriodo->Text = s2;
	EdCliente->Text = s3;
	EdPtoVenta->Text = s4;
	s5 = IntToStr(StrToInt(s5) + 1);
	EdNroComprobante->Text = s5;

	VerificarDatos(EdContribuyente);
	VerificarDatos(EdPeriodo);
	VerificarDatos(EdCliente);
	VerificarDatos(EdPtoVenta);
	VerificarDatos(EdNroComprobante);
	EdPtoVenta->SetFocus();
}
//---------------------------------------------------------------------------

AnsiString TCargarVentas::LimpiarNumero(AnsiString s)
{
	AnsiString aux;
	aux = s.SubString(3,s.Length());
	aux = aux.Delete(aux.Length()-2,1);
	aux = aux.Insert(".", aux.Length()-1);
    return aux;
}
//---------------------------------------------------------------------------

bool TCargarVentas::GuardarDatos(void)
{
   if(!(contOK && perOK && fechOK && cliOK && ptoOK && nroOK && ccOK && tipoOK && docOK && juriOK && al1OK && al2OK && al3OK && al4OK))
   {
	  Application->MessageBox(L"Hay errores en los datos ingresados.\nPor favor revise los casilleros resaltados",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return false;
   }

   if(idContribuyente == idCliente)
   {
	  Application->MessageBox(L"No pueden coincidir los cuits del informante y el cliente",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return false;
   }

   if(EdTipo->Text == "1")
   {
	  if(civaCont != 2 || civaCli != 2)
	  {
		 Application->MessageBox(L"Un comprobante A solo puede ser emitido y/o recibido por responsables inscriptos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 return false;
	  }
   }

   if(EdTipo->Text == "3")
   {
	  if(civaCont != 1 && civaCont != 4)
	  {
		 Application->MessageBox(L"Un comprobante C solo puede ser emitido por monotributistas o exentos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 return false;
	  }
   }

   if(Application->MessageBox(L"Se va a guardar la información ingresada, desea continuar?",L"Guardar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return false;

   if(modificando)
	  if(Application->MessageBox(L"Se van a modificar los datos de un comprobante previamente cargado\n\nREALMENTE DESEA CONTINUAR?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
		 return false;

   if(EdTotal->Text == "$ 0,00")
	  if(Application->MessageBox(L"Se va a cargar un comprobante con total $ 0,00, es correcto?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
		 return false;

   //si contOK y cliOK -> idContribuyente e idCliente contienen datos correctos

   AnsiString s;

   SQLQuery1->Close();
   SQLQuery1->SQL->Clear();

   if(!modificando)
   {
	  SQLQuery1->SQL->Add("INSERT INTO comprobantesventas VALUES (NULL, :v2, :v3, :v4, :v8, :v5, :v1, :v7, :v6, :v9, :v10, :v11, :v12, :v13, :v14, :v15, :v16, :v17, :v18, :v19, :v20, :v21, :v22, :v23, :v24, :v25, :v26, :v27)");
   }
   else
   {
	  SQLQuery1->SQL->Add("UPDATE comprobantesventas SET fechaPeriodo = :v1, fechaComprobante = :v2, ptoVenta = :v3, nroComprobante = :v4, refCliente = :v5, refDocumento = :v6, refTipo = :v7, refContribuyente = :v8, refCuentaVenta = :v9, refAlicuota1 = :v10, netoGravado1 = :v11, refAlicuota2 = :v12, netoGravado2 = :v13, refAlicuota3 = :v14, netoGravado3 = :v15, refAlicuota4 = :v16, netoGravado4 = :v17, retencionesIVA = :v18, percepcionesIVA = :v19, retencionesIB = :v20, percepcionesIB = :v21, retencionesGanancias = :v22, conceptosNoGravados = :v23, exentos = :v24, total = :v25, anulado = :v26, refJurisdiccion = :v27  WHERE(idComprobanteVenta = :id)");
	  SQLQuery1->ParamByName("id")->AsInteger = idModificado;
   }

	  SQLQuery1->ParamByName("v1")->AsDate = StrToDate("01/" + EdPeriodo->Text);
	  SQLQuery1->ParamByName("v2")->AsDate = StrToDate(EdFecha->Text);
	  SQLQuery1->ParamByName("v3")->AsInteger = StrToInt(EdPtoVenta->Text);
	  SQLQuery1->ParamByName("v4")->AsInteger = StrToInt(EdNroComprobante->Text);
	  SQLQuery1->ParamByName("v5")->AsInteger = idCliente;
	  SQLQuery1->ParamByName("v6")->AsInteger = StrToInt(EdDocumento->Text);
	  SQLQuery1->ParamByName("v7")->AsInteger = StrToInt(EdTipo->Text);
	  SQLQuery1->ParamByName("v8")->AsInteger = idContribuyente;
	  SQLQuery1->ParamByName("v9")->AsString = EdCuentaVenta->Text;

	  SQLQuery1->ParamByName("v10")->AsString = EdAlicuota1->Text;
	  SQLQuery1->ParamByName("v12")->AsString = EdAlicuota2->Text;
	  SQLQuery1->ParamByName("v14")->AsString = EdAlicuota3->Text;
	  SQLQuery1->ParamByName("v16")->AsString = EdAlicuota4->Text;


	  if(EdDocumento->Text != "3")
	  {
		 SQLQuery1->ParamByName("v11")->AsString = LimpiarNumero(EdNetoGravado1->Text);
		 SQLQuery1->ParamByName("v13")->AsString = LimpiarNumero(EdNetoGravado2->Text);
		 SQLQuery1->ParamByName("v15")->AsString = LimpiarNumero(EdNetoGravado3->Text);
		 SQLQuery1->ParamByName("v17")->AsString = LimpiarNumero(EdNetoGravado4->Text);

		 SQLQuery1->ParamByName("v18")->AsString = LimpiarNumero(EdRetencionesIVA->Text);
		 SQLQuery1->ParamByName("v19")->AsString = LimpiarNumero(EdPercepcionesIVA->Text);
		 SQLQuery1->ParamByName("v20")->AsString = LimpiarNumero(EdRetencionesIB->Text);
		 SQLQuery1->ParamByName("v21")->AsString = LimpiarNumero(EdPercepcionesIB->Text);
		 SQLQuery1->ParamByName("v22")->AsString = LimpiarNumero(EdRetencionesGanancias->Text);
		 SQLQuery1->ParamByName("v23")->AsString = LimpiarNumero(EdConcNoGravados->Text);
		 SQLQuery1->ParamByName("v24")->AsString = LimpiarNumero(EdExentos->Text);
		 SQLQuery1->ParamByName("v25")->AsString = LimpiarNumero(EdTotal->Text);
	  }
	  else
	  {
		 SQLQuery1->ParamByName("v11")->AsString = "-" + LimpiarNumero(EdNetoGravado1->Text);
		 SQLQuery1->ParamByName("v13")->AsString = "-" + LimpiarNumero(EdNetoGravado2->Text);
		 SQLQuery1->ParamByName("v15")->AsString = "-" + LimpiarNumero(EdNetoGravado3->Text);
		 SQLQuery1->ParamByName("v17")->AsString = "-" + LimpiarNumero(EdNetoGravado4->Text);

		 SQLQuery1->ParamByName("v18")->AsString = "-" + LimpiarNumero(EdRetencionesIVA->Text);
		 SQLQuery1->ParamByName("v19")->AsString = "-" + LimpiarNumero(EdPercepcionesIVA->Text);
		 SQLQuery1->ParamByName("v20")->AsString = "-" + LimpiarNumero(EdRetencionesIB->Text);
		 SQLQuery1->ParamByName("v21")->AsString = "-" + LimpiarNumero(EdPercepcionesIB->Text);
		 SQLQuery1->ParamByName("v22")->AsString = "-" + LimpiarNumero(EdRetencionesGanancias->Text);
		 SQLQuery1->ParamByName("v23")->AsString = "-" + LimpiarNumero(EdConcNoGravados->Text);
		 SQLQuery1->ParamByName("v24")->AsString = "-" + LimpiarNumero(EdExentos->Text);
		 SQLQuery1->ParamByName("v25")->AsString = "-" + LimpiarNumero(EdTotal->Text);
      }

	  if(ChAnulado->Checked)
		 SQLQuery1->ParamByName("v26")->AsInteger = 1;
	  else
		 SQLQuery1->ParamByName("v26")->AsInteger = 0;

      SQLQuery1->ParamByName("v27")->AsString = EdJurisdiccion->Text;

	  SQLQuery1->ExecSQL();

	  return true;
}
//---------------------------------------------------------------------------
void TCargarVentas::QuiereModificar(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  int a = 0;
	  if(!modificando)
		 a = YaExiste();
	  if(a != 0)
	  {
		 if(Application->MessageBox(L"Este comprobante ya existe, desea modificarlo?",L"Comprobante existente!?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
		 {
			TraerDatos(a);
			modificando = true;
			idModificado = a;
			CargarVentas->Caption = "*Modificando comprobante*";
			BtnAgregarComp->Caption = "Guardar cambios";
			BtnAgregarYCont->Caption = "Guardar y agregar otro";
			btEliminarComp->Enabled = true;
		 }
		 else
		 {
			if(Sender == EdDocumento || Sender == EdTipo)
			{
			   Edit->Text = "";
			   Edit->SetFocus();
			}
			else if(Sender == EdCliente)
			{
			   Edit->Text = "__-________-_";
			   Edit->SetFocus();
			}
			else if(Sender == EdNroComprobante)
			{
			   Edit->Text = "00000000";
			   Edit->SetFocus();
			}
			else if(Sender == EdPtoVenta)
			{
			   Edit->Text = "00000";
			   Edit->SetFocus();
			}
		 }
	  }
   }
}
//---------------------------------------------------------------------------



//***************************************************************************
//***************FIN DE DEFINICION DE FUNCIONES******************************
//***************************************************************************



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TCargarVentas::EdContribuyenteKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdContribuyente->Text = "___-________-_";
	  EdContribuyente->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdContribuyente->Text = "__-________-_";
	  EdContribuyente->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 7;
	  Opciones->soloMisClientes = true;
	  Opciones->ShowModal();
	  Key = NULL;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = Opciones->idRetorno;
	  AuxQuery->Open();
	  EdContribuyente->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdContribuyente->Text == "")
	     EdContribuyente->Text = "__-________-_";

	  EdPeriodo->SetFocus();
   }

   EdContribuyente->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TCargarVentas::EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdClienteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdCliente->SelStart == 2 || EdCliente->SelStart == 11)
	  EdCliente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdClienteKeyPress(TObject *Sender, System::WideChar &Key)

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
	  EdCliente->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdCliente->Text == "")
		 EdCliente->Text = "__-________-_";

	  EdPtoVenta->SetFocus();
   }

   EdCliente->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdClienteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdCliente->Text = "___-________-_";
	  EdCliente->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdCliente->Text = "__-________-_";
	  EdCliente->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdClienteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdCliente->SelStart == 2 || EdCliente->SelStart == 11)
	  EdCliente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdPeriodo->Text = "___/____";
	  EdPeriodo->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdPeriodo->Text = "__/____";
	  EdPeriodo->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key)

{
   EdPeriodo->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TCargarVentas::EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPeriodoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdFecha->Text = "__/__/____";
	  EdFecha->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdFecha->Text = "__/__/____";
	  EdFecha->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdFechaKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(fechOK && Key == '+')
   {
	  Key = NULL;
	  EdFecha->Text = DateToStr(IncDay(StrToDate(EdFecha->Text), 1));
   }
   if(fechOK && Key == '-')
   {
	  Key = NULL;
	  EdFecha->Text = DateToStr(IncDay(StrToDate(EdFecha->Text), -1));
   }
   else if(Key < '0' || Key > '9')
      Key = NULL;
   else
      EdFecha->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdFecha->SelStart == 2 || EdFecha->SelStart == 5)
	  EdFecha->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdFechaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdFecha->SelStart == 2 || EdFecha->SelStart == 5)
	  EdFecha->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdCuentaVentaKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
      Opciones->llamador = 2;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdCuentaVenta->Text = IntToStr(Opciones->idRetorno);
	  EdDocumento->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 3;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdDocumento->Text = IntToStr(Opciones->idRetorno);
	  EdTipo->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTipoKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 4;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdTipo->Text = IntToStr(Opciones->idRetorno);
	  EdJurisdiccion->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::BtnAgregarCompClick(TObject *Sender)
{
   if(GuardarDatos())
   {
	  AnsiString s1 = EdContribuyente->Text;
	  AnsiString s2 = EdPeriodo->Text;
	  AnsiString s3 = EdPtoVenta->Text;
	  AnsiString s4 = EdNroComprobante->Text;

	  RestablecerFormulario();

	  EdContribuyente->Text = s1;
	  EdPeriodo->Text = s2;
	  EdPtoVenta->Text = s3;
	  s4 = IntToStr(StrToInt(s4) + 1);
	  EdNroComprobante->Text = s4;

	  VerificarDatos(EdContribuyente);
	  VerificarDatos(EdPeriodo);
	  VerificarDatos(EdPtoVenta);
	  VerificarDatos(EdNroComprobante);
	  EdFecha->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdClienteExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPtoVentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNroComprobanteExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdDocumentoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTipoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado1Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado2Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado3Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado4Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIVAEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIVAEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIBEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIBEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesGananciasEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdConcNoGravadosEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdExentosEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTotalEnter(TObject *Sender)
{
   if(EdTipo->Text != "2" && EdTipo->Text != "3")
      ShowMessage("Atención! Se va a modificar manualmente el total. Verifique que la acción sea correcta");
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado1Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado2Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado3Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado4Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIVAExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIVAExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIBExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIBExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesGananciasExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdConcNoGravadosExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdExentosExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------


void __fastcall TCargarVentas::EdNetoGravado1KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado2KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado3KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado4KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIVAKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIVAKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIBKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIBKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesGananciasKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdConcNoGravadosKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdExentosKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTotalKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNetoGravado4MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIVAMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIVAMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesIBMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPercepcionesIBMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdRetencionesGananciasMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdConcNoGravadosMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdExentosMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTotalMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::BtnAgregarYContClick(TObject *Sender)
{
   if(GuardarDatos())
   {
	  RestablecerFormularioCont();
	  EdFecha->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::BtnCancelarClick(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a cancelar todos los cambios. Desea continuar?",L"Cancelar cambios?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	   RestablecerFormulario();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdContribuyenteExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPeriodoExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdFechaExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdCuentaVentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTotalExit(TObject *Sender)
{
   DarFormatoEdit(Sender);

   if(EdTipo->Text == "2")
   {
	  float aux = StrToFloat(EdTotal->Text.SubString(3,EdTotal->Text.Length()-2));
	  float aux2 = aux / 1.21;
	  EdNetoGravado1->Text = FormatFloat("$ 0.#0", aux2);
	  LabIVA1->Caption = FormatFloat("$ 0.#0", aux2 * 0.21);
   }

   BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::AgClienteClick(TObject *Sender)
{
   if(!cliOK)
   {
	  ModificarCuentas->RG->ItemIndex = 0;

      AgregarContribuyente->idContribuyente = idContribuyente;
      AgregarContribuyente->llamador = 3;
	  AgregarContribuyente->EdCUIT->Text = EdCliente->Text;
	  AgregarContribuyente->ShowModal();

	  VerificarDatos(EdCliente);

	  EdPtoVenta->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota1Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado1);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota2Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado2);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota3Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado3);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota4Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado3);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdAlicuota4MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdCuentaVentaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdDocumentoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdTipoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 5;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdJurisdiccion->Text = IntToStr(Opciones->idRetorno);
	  EdNetoGravado1->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdJurisdiccionExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(EdTipo->Text == "2" || EdTipo->Text == "3")
      EdTotal->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::EdJurisdiccionMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TCargarVentas::RG1Click(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------






void __fastcall TCargarVentas::btEliminarCompClick(TObject *Sender)
{
   if(!modificando)
	  return;

   if(Application->MessageBox(L"Atención! Se va a eliminar el comprobante seleccionado.",L"Eliminar comprobante?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;
   if(Application->MessageBox(L"Esta acción no puede deshacerse, realmente desea continuar?",L"Confirma eliminación?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
      return;

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add("DELETE FROM comprobantesventas WHERE(idComprobanteVenta = :id)");
   AuxQuery->ParamByName("id")->AsInteger = idModificado;
   AuxQuery->ExecSQL();

   RestablecerFormulario();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::btMostrarCompClick(TObject *Sender)
{
   if (!contOK || !perOK)
      return;

   fMostrarComprobantes->periodo = EdPeriodo->Text;
   fMostrarComprobantes->idContribuyente = idContribuyente;
   fMostrarComprobantes->llamador = 0;
   fMostrarComprobantes->ShowModal();


   if(fMostrarComprobantes->retorno > 0)
   {
      if(Application->MessageBox(L"Se van a reemplazar todos los datos por los del comprobante seleccionado, desea continuar?",L"Reemplazar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

      AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT fechaComprobante, ptoVenta, nroComprobante, refCliente, refDocumento, refTipo FROM comprobantesVentas WHERE(idComprobanteVenta = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = fMostrarComprobantes->retorno;
	  AuxQuery->Open();

	  EdPtoVenta->Text = AuxQuery->FieldByName("ptoVenta")->AsString;
	  EdNroComprobante->Text = AuxQuery->FieldByName("nroComprobante")->AsString;
	  EdDocumento->Text = AuxQuery->FieldByName("refDocumento")->AsString;
	  EdTipo->Text = AuxQuery->FieldByName("refTipo")->AsString;
	  EdFecha->Text = AuxQuery->FieldByName("fechaComprobante")->AsString;
	  int id = AuxQuery->FieldByName("refCliente")->AsInteger;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = id;
	  AuxQuery->Open();
	  EdCliente->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();


	  VerificarDatos(EdPtoVenta);
	  VerificarDatos(EdNroComprobante);
	  VerificarDatos(EdDocumento);
	  VerificarDatos(EdTipo);
	  VerificarDatos(EdCliente);


	  TraerDatos(fMostrarComprobantes->retorno);
	  modificando = true;
	  idModificado = fMostrarComprobantes->retorno;
	  CargarVentas->Caption = "*Modificando comprobante*";
	  BtnAgregarComp->Caption = "Guardar cambios";
	  BtnAgregarYCont->Caption = "Guardar cambios y agregar otro";
	  btEliminarComp->Enabled = true;
   }

}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::btEliminarCompExit(TObject *Sender)
{
   BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::BtnCancelarExit(TObject *Sender)
{
   if(!btEliminarComp->Enabled)
	  BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TCargarVentas::SpeedButton1Click(TObject *Sender)
{
   ModificarCuentas->RG->ItemIndex = 0;
   ModificarCuentas->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TCargarVentas::Edit1Exit(TObject *Sender)
{
   if(Edit1->Text != "")
   {
       AuxQuery->Close();
	   AuxQuery->SQL->Clear();
	   AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	   AuxQuery->ParamByName("v")->AsString= Edit1->Text;
	   AuxQuery->Open();
	   EdContribuyente->Text = AuxQuery->FieldByName("cuit")->AsString;
	   AuxQuery->Close();

	   if(EdContribuyente->Text == "")
		 EdContribuyente->Text = "__-________-_";
   }
   EdContribuyente->SetFocus();
   Edit1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TCargarVentas::Edit2Exit(TObject *Sender)
{
   if(Edit2->Text != "")
   {
       AuxQuery->Close();
	   AuxQuery->SQL->Clear();
	   AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	   AuxQuery->ParamByName("v")->AsString= Edit2->Text;
	   AuxQuery->Open();
	   EdCliente->Text = AuxQuery->FieldByName("cuit")->AsString;
	   AuxQuery->Close();

	   if(EdCliente->Text == "")
		 EdCliente->Text = "__-________-_";
   }
   EdCliente->SetFocus();
   Edit2->Clear();
}
//---------------------------------------------------------------------------

