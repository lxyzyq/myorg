
bool __fastcall TDataModule1::SyncKaoqinData(TObject* zkDevice)
{
  if (zk->ReadAllGLogData(1))
    {
      WideString  dwEnrollNumber = "123456789012345";
      long dwVerifyMode,dwInOutMode,dwYear,dwMonth,dwDay,dwHour,dwMinute,dwSecond,dwWorkCode;
      while (
	     zk->SSR_GetGeneralLogData(1,&dwEnrollNumber,&dwVerifyMode,&dwInOutMode,&dwYear,&dwMonth,&dwDay,
				       &dwHour,&dwMinute,&dwSecond,&dwWorkCode))
        {
	  TDateTime mDate =  TDateTime(dwYear,dwMonth,dwDay);
	  TDateTime mTime =   TDateTime(dwHour,dwMinute,dwSecond,0);

	  QKaoqinLog->Active = false;
	  QKaoqinLog->SQL->Clear();
	  QKaoqinLog->SQL->Add( "select top 1 * from 考勤记录  where datediff(mi,打卡时间, '");
	  QKaoqinLog->SQL->Add( (mDate+mTime).FormatString("yyyy-mm-dd hh:nn:ss")+"')");
	  QKaoqinLog->Active = true;

	  if(QKaoqinLog->RecordCount>0) continue;

	  QKaoqinLog->Append();
	  QKaoqinLog->FieldByName("考勤机号")->AsInteger= zk->MachineNumber;
	  QKaoqinLog->FieldByName("打卡工号")->AsString= dwEnrollNumber;
	  QKaoqinLog->FieldByName("打卡时间")->AsDateTime = mDate+mTime;
	  QKaoqinLog->UpdateBatch(arAll);
        }
      return true;
    } else
    return false;
}
