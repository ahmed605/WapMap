#ifndef H_C_SPRBANK
#define H_C_SPRBANK

#include <vector>
#include "hgeSprite.h"
#include "../shared/cREZ.h"
#include "../shared/cWWD.h"
#include "../shared/cPID.h"
#include "../shared/cProgressInfo.h"
#include "guichan/listmodel.hpp"

#include "../cDataController.h"

#define SPRBANK_TEXJUMPVIOLATION 0
#define SPRBANK_TEXLOCKVIOLATION 1

class cTextureAtlaser;
class cBankImageSet;
class cSprBankAsset;

class cSprBankAssetIMG : public cAsset, public cImage {
 private:
  cSprBankAsset * hIS;
  int m_iID;
  int m_iIT;

  cSprBankAssetIMG(int it, cBankImageSet * par, cSprBankAsset * is, int id);
  ~cSprBankAssetIMG();
 public:
  hgeSprite * GetSprite(){ return imgSprite; };
  int GetID(){ return m_iID; };
  int GetIt(){ return m_iIT; };

  virtual void Load();
  virtual void Unload();

  virtual std::string GetMountPoint();

 friend class cBankImageSet;
 friend class cSprBankAsset;
};

class cSprBankAsset {
 protected:
  std::string strID;
  std::string strHash;
  std::vector<cSprBankAssetIMG*> m_vSprites;
  int m_iSize;
  int m_iMaxID;
  cSprBankAsset(std::string id);
  ~cSprBankAsset();
  void DeleteIMG(cSprBankAssetIMG * img);
  void AddIMG(cSprBankAssetIMG * img);
 friend class cBankImageSet;
 public:
  cSprBankAssetIMG * GetIMGByIterator(int it);
  cSprBankAssetIMG * GetIMGByID(int id);
  cSprBankAssetIMG * GetIMGByNoID(int noid);
  int GetMaxIMGID(){ return m_iMaxID; };
  int GetSpritesCount(){ return m_vSprites.size(); };
  const char * GetID(){ return strID.c_str(); };
  int GetSize(){ return m_iSize; };
  std::string GetHash(){ return strHash; };

  void SortAndFixIterators();
  void UpdateHash();
};

class cBankImageSet: public gcn::ListModel, public cAssetBank {
 private:

  cTextureAtlaser * myAtlaser;

  std::vector<cSprBankAsset*> m_vAssets;

  REZ::Parser * hREZ;
  PID::Palette * hPAL;
  WWD::GAME iGame;

  int m_iAssetsSize;

  bool bBatchProcess;
  int iBatchPackageCount;
 public:
  cBankImageSet();
  ~cBankImageSet();

  cTextureAtlaser * GetTextureAtlaser(){ return myAtlaser; };

  cSprBankAsset * GetAssetByID(const char * pszID);
  cSprBankAsset * GetAssetByIterator(int iIT){ return m_vAssets[iIT]; }

  int GetAssetsCount(){ return m_vAssets.size(); };
  int GetAssetsSize(){ return m_iAssetsSize; };
  void SortAssets();

  hgeSprite * GetObjectSprite(WWD::Object * obj);
  hgeSprite * GetSpriteFromAsset(const char * asset, int frame);
  WWD::Rect GetObjectRenderRect(WWD::Object * obj);
  WWD::Rect GetSpriteRenderRect(hgeSprite * spr);

  void SetGame(WWD::GAME g){ iGame = g; };

  //inherited from listmodel
  std::string getElementAt(int i);
  int getNumberOfElements();


  virtual void BatchProcessStart(cDataController * hDC);
  virtual void BatchProcessEnd(cDataController * hDC);
  virtual std::string GetFolderName(){ return std::string("IMAGES"); };
  virtual std::string GetMountPointForFile(std::string strFilePath, std::string strPrefix);
  virtual cAsset * AllocateAssetForMountPoint(cDataController * hDC, cDC_MountEntry mountEntry);
  virtual void DeleteAsset(cAsset * hAsset);
};

#endif
