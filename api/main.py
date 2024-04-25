from typing import Union
from fastapi import FastAPI

app = FastAPI()


@app.get("/")
async def read_root():
    return {"Hello": "World"}

@app.get("/api/noob/health")
async def read_health():
    return {"status": "ok"}

@app.get("/items/{item_id}")
async def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}

@app.get ("api/withdraw")
async def withdraw(amount: int):
    return {"amount": amount}

@app.get ("api/accountinfo")
async def account_info(firstname: str, lastname: str, balance: int):
    return {"firstname ": firstname, "lastname ": lastname, "balance ": balance}