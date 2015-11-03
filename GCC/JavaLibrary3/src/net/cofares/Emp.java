/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.cofares;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author pascalfares
 */
@Entity
@Table(name = "Emp")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Emp.findAll", query = "SELECT e FROM Emp e"),
    @NamedQuery(name = "Emp.findByIdEmp", query = "SELECT e FROM Emp e WHERE e.idEmp = :idEmp"),
    @NamedQuery(name = "Emp.findByEmpcol", query = "SELECT e FROM Emp e WHERE e.empcol = :empcol"),
    @NamedQuery(name = "Emp.findByEmail", query = "SELECT e FROM Emp e WHERE e.email = :email")})
public class Emp implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "idEmp")
    private Integer idEmp;
    @Basic(optional = false)
    @Column(name = "Empcol")
    private String empcol;
    @Column(name = "email")
    private String email;
    @JoinColumn(name = "idDep", referencedColumnName = "idDep")
    @ManyToOne
    private Dep idDep;

    public Emp() {
    }

    public Emp(Integer idEmp) {
        this.idEmp = idEmp;
    }

    public Emp(Integer idEmp, String empcol) {
        this.idEmp = idEmp;
        this.empcol = empcol;
    }

    public Integer getIdEmp() {
        return idEmp;
    }

    public void setIdEmp(Integer idEmp) {
        this.idEmp = idEmp;
    }

    public String getEmpcol() {
        return empcol;
    }

    public void setEmpcol(String empcol) {
        this.empcol = empcol;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Dep getIdDep() {
        return idDep;
    }

    public void setIdDep(Dep idDep) {
        this.idDep = idDep;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idEmp != null ? idEmp.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Emp)) {
            return false;
        }
        Emp other = (Emp) object;
        if ((this.idEmp == null && other.idEmp != null) || (this.idEmp != null && !this.idEmp.equals(other.idEmp))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "net.cofares.Emp[ idEmp=" + idEmp + " ]";
    }
    
}
