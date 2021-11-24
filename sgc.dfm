object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Sistema de Gesti'#243'n de Comprobantes'
  ClientHeight = 393
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 88
    Top = 32
    Width = 206
    Height = 324
  end
  object Button2: TButton
    Left = 96
    Top = 39
    Width = 190
    Height = 25
    Caption = 'Liquidar compras'
    TabOrder = 0
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 96
    Top = 180
    Width = 190
    Height = 28
    Caption = 'Agregar / Modificar Contribuyente'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button6: TButton
    Left = 96
    Top = 86
    Width = 190
    Height = 25
    Caption = 'Liquidar ventas'
    TabOrder = 1
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 96
    Top = 277
    Width = 190
    Height = 25
    Caption = 'Asociaci'#243'n de cuentas'
    TabOrder = 5
    OnClick = Button7Click
  end
  object Button4: TButton
    Left = 96
    Top = 133
    Width = 190
    Height = 25
    Caption = 'Reportes'
    TabOrder = 2
    OnClick = Button4Click
  end
  object Button1: TButton
    Left = 96
    Top = 324
    Width = 190
    Height = 25
    Caption = 'Eliminar comprobantes'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button5: TButton
    Left = 96
    Top = 230
    Width = 190
    Height = 25
    Caption = 'Agregar / Modificar cuentas'
    TabOrder = 4
    OnClick = Button5Click
  end
end
