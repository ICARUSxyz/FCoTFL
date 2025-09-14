import os, re, json, time
from openai import OpenAI

# ==== Fixed configuration ====
PROMPT_DIR = "Datasets/UnseenCode-FL/Prompt"
OUTPUT_DIR = "Results/SimpleRuns/UnseenCode-FL"
MODEL = "gpt-5"   # Change to "gpt-4o" or "gpt-4-turbo" if needed
SYSTEM_PROMPT = ""
TEMPERATURE = 0.7
MAX_TOKENS = 2048
N = 1            # Number of candidates per file
RETRIES = 3      # Retry times if API fails

# ==== API Key ====
# Replace "your openai key" with your actual OpenAI API key
OPENAI_API_KEY = "your openai key"

# ==== Helper functions ====
def natural_key(s: str):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", s)]

def read_text(path: str) -> str:
    with open(path, "r", encoding="utf-8") as f:
        return f.read()

def write_json(path: str, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)

# ==== Main logic ====
def main():
    # Initialize OpenAI client with explicit API key
    client = OpenAI(api_key=OPENAI_API_KEY)

    files = [f for f in os.listdir(PROMPT_DIR)
             if os.path.isfile(os.path.join(PROMPT_DIR, f))
             and f.lower().endswith((".txt", ".md", ".json", ".prompt"))]
    files = sorted(files, key=natural_key)

    print(f"[INFO] Found {len(files)} files in {PROMPT_DIR}")
    for idx, fn in enumerate(files, 1):
        path = os.path.join(PROMPT_DIR, fn)
        prompt = read_text(path)
        print(f"[{idx}/{len(files)}] Sending {fn} ...")

        tries, outputs = 0, None
        while tries < RETRIES:
            try:
                resp = client.chat.completions.create(
                    model=MODEL,
                    temperature=TEMPERATURE,
                    max_tokens=MAX_TOKENS,
                    n=N,
                    messages=[
                        {"role": "system", "content": SYSTEM_PROMPT},
                        {"role": "user", "content": prompt},
                    ],
                )
                outputs = [c.message.content for c in resp.choices]
                break
            except Exception as e:
                tries += 1
                print(f"[RETRY] {fn} ({tries}/{RETRIES}) error: {e}")
                time.sleep(2 * tries)

        if outputs is None:
            outputs = [f"[ERROR] Could not get response for {fn}"]

        save_path = os.path.join(OUTPUT_DIR, fn + ".json")
        payload = {
            "file": fn,
            "model": MODEL,
            "responses": outputs,
        }
        write_json(save_path, payload)
        print(f"[OK] Saved -> {save_path}")

if __name__ == "__main__":
    main()
