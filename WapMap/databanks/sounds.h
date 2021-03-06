#ifndef H_C_SNDBANK
#define H_C_SNDBANK

#include <vector>
#include <hge.h>
#include "../shared/cREZ.h"
#include "../shared/cProgressInfo.h"
#include <sys/types.h>
#include <guichan/listModel.hpp>
#include "../cDataController.h"

class cSndBankAsset : public cAsset {
 protected:
  HEFFECT m_snd;
  cSndBankAsset(cFile hFile, std::string id);
  ~cSndBankAsset();
 friend class cBankSound;
 public:

  virtual void Load();
  virtual void Unload();

  HEFFECT GetSound(){ return m_snd; };

  virtual std::string GetMountPoint();
};

class cBankSound : public gcn::ListModel, public cAssetBank {
 private:

  std::vector<cSndBankAsset*> m_vAssets;

  bool bBatchProcessing;
  char * szPath;
  REZ::Parser * hREZ;
  bool bUseREZ;
  int iBatchPackageCount;
 public:
  cBankSound();
  ~cBankSound();

  cSndBankAsset * GetAssetByID(const char * pszID);
  cSndBankAsset * GetAssetByIterator(int iIT){ if( iIT < 0 || iIT >= m_vAssets.size() ) return NULL; return m_vAssets[iIT]; }

  int GetAssetsCount(){ return m_vAssets.size(); };
  //inherited
  std::string getElementAt(int i);
  int getNumberOfElements();

  void SortAssets();

  virtual void BatchProcessStart(cDataController * hDC);
  virtual void BatchProcessEnd(cDataController * hDC);

  virtual void ProcessAssets(cAssetPackage * hClientAP, std::vector<cFile> vFiles);
  virtual std::string GetFolderName(){ return std::string("SOUNDS"); };
};

#endif
