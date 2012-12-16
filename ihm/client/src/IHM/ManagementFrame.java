/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import client.Client;
import client.Command;
import client.ThreadLog;
import javax.swing.JFrame;
import javax.swing.JProgressBar;

/**
 *
 * @author
 * Elodie
 */
public class ManagementFrame extends javax.swing.JFrame implements ThreadLog.LogReceiver {
	
	Command threadCmd;
	ThreadLog threadLog;
	//warehouse disponibility 
	int palAWarehouse;
	int palBWarehouse;
	// number of pallets to produce
	int nbPalA;
	int nbPalB;
	//current situation
	int nbCurrentBox;
	int nbCurrentBin;
	String currentLot;
	private ParametersFrame paramsFrame;
	
	public void setParamsFrame(ParametersFrame p) {
		this.paramsFrame = p;
	}
	
	public int getPalAWarehouse() {
		return palAWarehouse;
	}
	
	public int getPalBWarehouse() {
		return palBWarehouse;
	}
	
	public void setParameters(String lot, int qte) {
		lotProgressBar.setMaximum(qte);
		lotProgressBar.setValue(0);
		this.currentLot = lot;
		lotProgressBar.setStringPainted(true);
		this.descriptionLabel.setText("État de fabrication du lot" + lot);
		//initialization of data
		if (currentLot.equalsIgnoreCase("A")) {
			this.palAWarehouse = 0;
			this.palBWarehouse = 0;
			this.nbPalA = qte;
		} else { //lot == "B"
			this.palAWarehouse = 0;
			this.palBWarehouse = 0;
			this.nbPalB = qte;
		}
	}

	/**
	 * Creates
	 * new
	 * form
	 * ManagementFrame
	 */
	public ManagementFrame(Command threadCmd, ThreadLog threadLog) {
		initComponents();
		this.threadCmd = threadCmd;
		this.threadLog = threadLog;
		threadLog.setLogReceiver(this);
		this.logTextArea.setEditable(false);
	}
	boolean currentErrorState = false;
	
	@Override
	public void setVisible(boolean visibility) {
		if (currentErrorState) {
			visibility = false;
		}
		super.setVisible(visibility);
	}
	
	public void addLog(String log) {
		logTextArea.append(log + "\r\n");
	}

	/**
	 * This
	 * method
	 * is
	 * called
	 * from
	 * within
	 * the
	 * constructor
	 * to
	 * initialize
	 * the
	 * form.
	 * WARNING:
	 * Do
	 * NOT
	 * modify
	 * this
	 * code.
	 * The
	 * content
	 * of
	 * this
	 * method
	 * is
	 * always
	 * regenerated
	 * by
	 * the
	 * Form
	 * Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        descriptionLabel = new javax.swing.JLabel();
        newCmdButton = new javax.swing.JButton();
        logScrollPane = new javax.swing.JScrollPane();
        logTextArea = new javax.swing.JTextArea();
        lotProgressBar = new javax.swing.JProgressBar();
        currentBox = new javax.swing.JLabel();
        currentBin = new javax.swing.JLabel();
        currentPal = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Suivi de la chaine de production");
        setResizable(false);

        descriptionLabel.setText("Etat de fabrication du lot");

        newCmdButton.setText("Nouvelle commande");
        newCmdButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newCmdButtonActionPerformed(evt);
            }
        });

        logTextArea.setColumns(20);
        logTextArea.setRows(5);
        logScrollPane.setViewportView(logTextArea);

        currentBox.setText("Carton en cours de remplissage : ");

        currentBin.setText("Taux de rebus dans le carton en cours :");

        currentPal.setText("currentPal");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(22, 22, 22)
                        .addComponent(lotProgressBar, javax.swing.GroupLayout.PREFERRED_SIZE, 239, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(currentPal, javax.swing.GroupLayout.DEFAULT_SIZE, 198, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(currentBox))
                            .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(currentBin)))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(logScrollPane)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(descriptionLabel)
                                    .addComponent(newCmdButton, javax.swing.GroupLayout.PREFERRED_SIZE, 193, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(0, 0, Short.MAX_VALUE)))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(descriptionLabel)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(lotProgressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(currentPal))
                .addGap(35, 35, 35)
                .addComponent(currentBox)
                .addGap(18, 18, 18)
                .addComponent(currentBin)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 42, Short.MAX_VALUE)
                .addComponent(logScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 173, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(newCmdButton)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void newCmdButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newCmdButtonActionPerformed
		NewCmdFrame newCmd = new NewCmdFrame(this, this.threadCmd);
		newCmd.setVisible(true);
    }//GEN-LAST:event_newCmdButtonActionPerformed
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel currentBin;
    private javax.swing.JLabel currentBox;
    private javax.swing.JLabel currentPal;
    private javax.swing.JLabel descriptionLabel;
    private javax.swing.JScrollPane logScrollPane;
    private javax.swing.JTextArea logTextArea;
    private javax.swing.JProgressBar lotProgressBar;
    private javax.swing.JButton newCmdButton;
    // End of variables declaration//GEN-END:variables

	@Override
	public void onReveiveLog(String log) {
		if (log.substring(0, 5).equalsIgnoreCase("STATE")) {
			//update the data
			//the server has sent : STATE-NBA-NBB-NbBoitesProduite-NbPiecesRefusées
			this.nbCurrentBin = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));			
			this.currentBin.setText("Nombre de pièces dans le rebut : " + nbCurrentBin);
			
			this.nbCurrentBox = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));
			this.currentBox.setText("Carton en cours de remplissage : n°" + nbCurrentBox);
			
			this.palBWarehouse = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));
			
			this.palAWarehouse = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			if (currentLot.equalsIgnoreCase("A")) {
				this.lotProgressBar.setValue(palAWarehouse);
				this.currentPal.setText(palAWarehouse + "/" + nbPalA);
			} else {
				this.lotProgressBar.setValue(palBWarehouse);
				this.currentPal.setText(palBWarehouse + "/" + nbPalB);
			}			
		} else {
			//it is a log, we add it in the TextArea
			addLog(log);
			logTextArea.setCaretPosition(logTextArea.getDocument().getLength());
		}
	}
	ErrorPopup ep = new ErrorPopup();
	
	@Override
	public void onReceiveError(ThreadLog.ERROR error) {
		String err = "";
		
		switch (error) {
			case BOX:
				err = "Carton manquant.";
				break;
			case BOX_REFUSED:
				err = "Taux d'erreur trop élevé à la mise en carton.";
				break;
			case PALETTE:
				err = "Palette manquante.";
				break;
			case PALETTE_QUEUE:
				err = "File d'attente de la mise en palette surchargée.";
				break;
			case PRINT:
				err = "L'imprimante.";
				break;
		}
		this.ep.setCommand(threadCmd);
		this.ep.setMgFrame(this);
		this.ep.getErrorNameLabel().setText(err);
		this.currentErrorState = true;
		this.setVisible(false);
		this.ep.setVisible(true);
	}
	
	public void setCurrentErrorState(boolean errorState) {
		this.currentErrorState = errorState;
	}
	GameOverPopup goPopup = new GameOverPopup();
	
	@Override
	public void onGameOver() {
		this.hide();
		this.goPopup.setCommand(threadCmd);
		this.goPopup.setParamsFrame(this.paramsFrame);
		this.goPopup.show();
	}
}
